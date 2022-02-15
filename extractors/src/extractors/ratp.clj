(ns extractors.ratp
  (:require [clj-http.core :as h]
            [tools.io :as tio]
            [clojure.tools.logging :as log]
            [com.rpl.specter :as sp]
            [net.cgrand.enlive-html :as html]
            [clojure.string :as str]))

;;; ========================
;;;     Extract Models
;;; ========================

(def base-uri
  "https://metro-parisien.mrsy.fr/ligne")

(def lines
  #{"1" "2" "3" "3bis" "4" "5" "6"
    "7" "7bis" "8" "9" "10" "11" "12"
    "13" "14"})

(def parc-header
  ["Numero" "Materiel" "Mise En Service" "Livree" "Affectation"
   "Arrive Sur La Ligne" "Status" "Provenance"])

(defn- fetch-page [url]
  (html/html-resource (java.net.URL. url)))

(defn- fetch-line [line]
  (fetch-page (format "%s?ligne=%s" base-uri
                      line)))

(defn image->line [node]
  (let [c (some->> (:content node)
                   (map (comp :src :attrs))
                   (remove nil?)
                   last)]
    (when c
      (-> (str/replace c #"https://metro-parisien.mrsy.fr/fichiers/pictos/" "")
          (str/replace #"genRVB.svg" "")))))

(defn extract-table [page]
  (let [table (-> (html/select page [:#parc])
                  (html/select [:table]))]
    (->> (html/select table [:tr])
         (map #(html/select % [:td]))
         (map
          (fn [x]
            (map (fn [y]
                   (let [txt (html/text y)
                         line (image->line y)]
                     (if (= "  " txt)
                       line
                       txt)))
                 x)))
         (drop 1))))

(defn retrieve-parc [line]
  (some->> (fetch-line line)
           extract-table
           (map vec)
           vec))

(defn populate-file []
  (doseq [l lines]
    (log/info "processing" l)
    (->> (retrieve-parc l)
         (tio/write-csv-file "/tmp/parc-ratp.csv"
                             {:append true}))))

(comment
  (populate-file):)
