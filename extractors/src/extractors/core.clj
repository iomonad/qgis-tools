(ns extractors.core
  (:require [clj-http.client :as http]
            [jsonista.core :as j]
            [clojure.java.io :as io]
            [clojure.data.csv :as csv]
            [environ.core :refer [env]])
  (:import [java.io File]))


;;; Helpers

(defn write-csv [path row-data]
  (let [columns (-> row-data first keys vec)
        headers (map name columns)
        rows (mapv #(mapv % columns) row-data)]
    (with-open [file (io/writer path)]
      (csv/write-csv file (cons headers rows)))))


(def mapper
  (j/object-mapper
   {:encode-key-fn name
    :decode-key-fn keyword}))


(defn reverse-geocode
  [long lat]
  (when (and long lat)
    (if-let [token (env :mapbox-token)]
      (-> (http/get (format "https://api.mapbox.com/geocoding/v5/mapbox.places/%s,%s.json?access_token=%s"
                            (str long) (str lat) token)
                    {:content-type "application/json"})
          :body
          (j/read-value mapper)
          :features
          first
          :place_name))))


(defn- transform-entity
  [data-keys {:keys [properties type geometry id] :as prop}]
  (let [[long lat] (try (-> (:coordinates geometry)
                            ffirst)
                        (catch Exception e
                          [0 0]))]
    (-> properties
        (select-keys data-keys)
        (assoc :address (reverse-geocode long lat))
        (into (sorted-map)))))


(defn- geojson->csv
  [^File file data-keys]
  (let [features (-> file slurp (j/read-value mapper)
                     :features)]
    (->> features
         (map (partial transform-entity data-keys)))))


(defn enedis-data->csv [input output]
  (let [header [:ref:FR:RTE
                :building
                :name
                :source
                :voltage
                :ref:FR:RTE_nom
                :power
                :substation
                :operator
                :location]]
    (->> (geojson->csv input header)
         (write-csv output))))

(comment
  (enedis-data->csv "/home/iomonad/downloads/export.geojson"
                    "/home/iomonad/export.csv"))
