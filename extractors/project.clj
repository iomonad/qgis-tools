(defproject extractors "0.0.1-SNAPSHOT"
  ;; ----------------------------------------------------------
  :dependencies [[clj-http                   "3.12.3"]
                 [instaparse                 "1.4.10"]
                 [integrant                  "0.8.0"]
                 [metosin/jsonista           "0.3.4"]
                 [metosin/sieppari           "0.0.0-alpha13"]
                 [org.clojure/clojure        "1.10.1"]
                 [org.clojure/core.async     "1.3.618"]
                 [org.clojure/tools.logging  "1.1.0"]
                 [org.clojure/data.csv       "1.0.0"]
                 [prismatic/schema           "1.1.12"]
                 [environ                    "1.2.0"]
                 [enlive                     "1.1.6"]
                 [com.rpl/specter            "1.1.3"]
                 [com.oscaro/tools-io        "0.3.23"]]
  ;; ----------------------------------------------------------
  :repl-options {:init-ns user})
