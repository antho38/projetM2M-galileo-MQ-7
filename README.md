projetM2M-galileo-MQ-7
======================

Ce mini-projet consiste a mettre en place une infrastructure de collecte de données capteur (ici un capteur de CO). L'acquisition des mesures de capteur se fait sur une carte Intel Galileo. Les données sont remontées dans des messages vers un serveur (mongoose) via un "broker" PubSub MQTT (Mosquitto). Les données sont stockées dans une base de données (MongoDB) et peuvent être visualisées en différé ou en direct (OpenHab). 
