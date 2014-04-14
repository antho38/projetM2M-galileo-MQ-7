projetM2M-galileo-MQ-7
======================

Auteur : BROGUY Anthony, KIEFFER Anthony

I. Contexte M2M et le domaine d'application ciblée
==================================================
  Ce mini-projet consiste a mettre en place une infrastructure de collecte de données provenant de capteur (ici un capteur de CO). L'acquisition des mesures de capteur se fait sur une carte Intel Galileo. Les données sont remontées dans des messages via un "broker" PubSub MQTT (Mosquitto) vers un serveur NodeJs (Mongoose) pour être ensuite stockées dans une base de données (MongoDB). Les données peuvent être visualisées en différé à partir de la base de donnée ou en direct à l’aide d’OpenHab qui est connécté au broker(comme pour le serveur) pour recevoir les messages. 

II. Architecture implémentée
============================
![diagramme](https://raw.githubusercontent.com/antho38/projetM2M-galileo-MQ-7/master/images/DiagrammeM2M.png)
Diagramme représentant l’architecture

  Ce diagramme nous permet de visualiser les interactions des composants matériels et logiciels utilisés sur les différents systèmes pour ce projet. 

III. Les composants logiciels et matériels utilisés
===================================================
1. Matériel
-----------
### 1.1 Ordinateur
  Nous avons utilisé 2 machines différentes : un ordinateur portable sous Windows 8.1 et un ordinateur portable sous Kubuntu 13.10.

### 1.2 Intel Galileo
![galileo](https://raw.githubusercontent.com/antho38/projetM2M-galileo-MQ-7/master/images/galileo.png)
Nous avons utilisé une carte Intel Galileo. Cette carte à la particularité d’avoir un port microSD permettant l'exécution d’un OS Linux.
    Pour plus d’informations : 
    
[Site arduino : rubrique galileo](http://arduino.cc/en/ArduinoCertified/IntelGalileo)

[Site intel : rubrique galileo](http://www.intel.com/content/www/us/en/do-it-yourself/galileo-maker-quark-board.html)

[Intel galileo getting started](https://communities.intel.com/servlet/JiveServlet/previewBody/22204-102-1-25429/Galileo_GettingStarted_329685_005.pdf)

### 1.3 Capteur MQ-7
![MQ-7](https://raw.githubusercontent.com/antho38/projetM2M-galileo-MQ-7/master/images/MQ-7.png)
Le capteur MQ-7 est un capteur de monoxyde de carbone (CO).
    La documentation technique de ce capteur peut être consultée ici : [lien](https://www.sparkfun.com/datasheets/Sensors/Biometric/MQ-7.pdf)

### 1.4 Autre matériels
-  1 Carte microSD 16 Go
-  1 cable usb > microUsb
-  1 cable ethernet
2. Logiciel
-----------
### 2.1 Intel Galileo Arduino SW 1.5.3
  IDE Arduino modifié pour fonctionner avec la carte Galileo. Cet environnement permet de configurer la carte et de récuperer ou d’envoyer des valeur sur ses différents ports.
  Cet IDE est téléchargeable ici : [lien](https://communities.intel.com/docs/DOC-22226)

### 2.2 [Mosquitto](http://mosquitto.org/)
![mosquitto](http://mosquitto.org/wp-content/themes/corp-mosq/images/mosquitto-50x35.png)
  “Mosquitto est un broker open source (licence BSD) qui implémente la version du protocole MQ Telemetry Transport (MQTT) 3.1. MQTT fournit une méthode légère permettant de réaliser une messagerie utilisant un modèle de publication / abonnement.” [Traduction du site mosquitto.org]
  
### 2.3 [NodeJs](http://nodejs.org/)
![nodeJS](https://raw.githubusercontent.com/antho38/projetM2M-galileo-MQ-7/master/images/nodeJS.png)
  “Node.js est une plate-forme construite sur l'exécution JavaScript de Chrome pour construire facilement des applications de réseau rapides et évolutives. Node.js utilise un modèle d’entrées / sorties évenementielle non bloquant qui le rend léger et efficace, idéal pour les applications en temps réel et les dispositifs distribués.” [Traduction du site nodejs.org]

### 2.4 [MongoDB](https://www.mongodb.org/)
![mongoDB](https://raw.githubusercontent.com/antho38/projetM2M-galileo-MQ-7/master/images/mongoDB.png)
  MongoDB est une base de données de type NoSQL écrite en C++.

### 2.5 [Mongoose](http://mongoosejs.com/)
  Mongoose permet de gérer une base de données de type mongoDB grâce à nodeJS.

###2.6 [OpenHab](http://www.openhab.org/)
![openHab](http://www.openhab.org/images/openhab-logo-top.png)
Le logiciel OpenHab permet de réaliser rapidement des interfaces d’applications connectées pour différents supports (PC, tablettes, smartphones)

3. Notre montage
----------------
![montage](https://raw.githubusercontent.com/antho38/projetM2M-galileo-MQ-7/master/images/montage.jpg)
Sur la photo ci dessus, on peut avoir un aperçu de la galileo avec le capteur. Le fil rouge est connecté au port 5V, le vert à la terre (GND) le noir à A0 et le blanc à D0.

IV. Les métriques (sloc, performance ...)
=========================================
  Durant ce projet peu de lignes de codes ont été écrites, environ 150 LOC. En effet seuls des fichiers de configurations on été codés, par exemple pour récupérer les données du capteur sur la carte, ou encore pour permettre la connexion entre le serveur Mongoose, l’application OpenHab et le broker Mosquitto. Du code a aussi été requis pour l’élaboration de l’interface web à partir d’OpenHab.
  Estimation du nombre de lignes de code : 
  -  script shell sur galileo : 10
  -  script nodeJs / mongoose : ~60
  -  sketch arduino : 25
  -  configuration openHab : ~50
  
Les valeurs de concentration de gaz Co (unité ppm) sont  recueillies toutes les demi-secondes sur la carte à partir du capteur et envoyées directement sur le broker. Ainsi l’interface web d’OpenHab se rafraîchie dans le même temps pour afficher les valeurs recueillies par le capteur.

Estimation de temps : 
  -  Actualisation du capteur < 0.5s
  -  Envoi sur le broker + transfert BD < 1s

V. Les problèmes rencontrés et les solutions élaborées
======================================================
1. Compatibilité avec Windows
-----------------------------
  La compatibilité avec Windows de certains logiciels ou opérations nous à parfois posé problème. Par exemple, l’utilisation du broker Mosquitto sur Windows est possible mais n’est vraiment pas intuitive. Un autre exemple : la communication de la carte vers l’extérieur lorsqu’elle est connecté à un ordinateur sous Windows. Configurer un Windows pour le mettre en mode routeur n’est pas aussi simple que sous un Linux.
    La solution évidente de ce problème a été d’utiliser un OS Linux (Kubuntu).
    
    Remarque : Ce problème peut être facilement résolu pour des informaticiens mais une personne lambda qui voudrait utiliser une carte Galileo comme nous l’avons fait pourrait ne pas y arriver ou cela lui prendrai énormément de temps.

2. Configurer l’interface ethernet de la Galileo
------------------------------------------------
  Pour configurer l’interface eth0 de la Galileo, des informations nous ont été fournies ici : [lien](http://air.imag.fr/index.php/SmartCampus2014/Tutoriels#Configuration_de_la_carte_Galileo). Cependant, cela n’a pas fonctionner pour nous.
  Pour parer à ce problème, nous avons utiliser le logiciel Wireshark pour écouter les communication sur l’interface eth du PC. Lorsque la carte démarre, elle envoie une requête de type UDP/DHCP. Cette requête nous à permis de récupérer l’adresse IP de la carte et donc de pouvoir configurer notre interface pour nous connecter en ssh sur la carte.

3. Execution du sketch écrit via l'IDE pour récuperer la valeur sur A0 sur l'OS
-------------------------------------------------------------------------------
  Pour tester le capteur MQ-7 et récupérer les valeurs qu'ils renvoyait, nous avons tout d'abord écrit un sketch via l'IDE arduino. Une fois que tout fonctionnait, nous avons voulu executer ce sketch sur l'OS installé sur la carte SD de la galileo. Après plusieurs heures de recherche, nous avons finalement changé d'idée et opté pour un script shell permettant,pare manipulation complexe, de récupérer la valeur de A0.

VI. Conclusion
==============
  Ce projet nous a permis de mettre en pratique de nouvelles notions sur les communications entre dispositifs. Nous avons découvert comment recueillir à partir d’une carte microcontroleur Galileo des données provenant d’un capteur. Nous avons aussi eu la possibilité d’utiliser un broker reposant sur le modèle de type publish/subscribe pour gérer les communication entre les dispositifs, ou encore d’utiliser un serveur se basant sur NodeJs pour stocker les valeurs dans une base de donnée. Et pour finir nous avons eu un aperçu de comment envoyer ou récupérer des données de divers dispositifs distants sur un réseau grâce à une interface web OpenHab.
Nous avons été confronté à la situation d’aujourd’hui en entreprise, qui est non plus de développer ses composants logiciels mais plutôt d’intégrer des composants entre eux. Il y a eu donc peu de code produit, mais en contre partie de nombreuses configurations pour faire communiquer les divers composants logiciels et matériels.

VII. Perspectives possibles à notre développement
=================================================
  Nous avons travaillé sur un capteur de monoxyde de carbone. Notre développement pourrait être adapté principalement à 2 types d’utilisation : 
  
1.  Utilisation expérimentale : 

  La sonde de CO pourrait permettre diverse expériences en laboratoire (ou non) concernant des mesures de monoxyde de carbone. L’architecture mise en place permettrait de collecter facilement les données pour les interpréter ou produire des statistiques (Exemple: Statistique de rejet de CO par un pot d'échappement). 

2.  Utilisation en maison : 

  On pourrait implémenter un système domotique sur l’OS de la carte Galileo ou relier la Galileo en réseau à un système domotique existant. Couplé au capteur de CO, cela permettrait de mesurer le taux de CO dans l’air d’une maison et d’automatiser l’ouverture de fenêtres ou d’une porte de garage quand le taux atteindrai un seuil critique. 
