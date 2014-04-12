#!/bin/sh

#Pour lire l'analog A0 sur la carte
#La première commande echo exports GPIO port 37 qui est uilisé pour controler l'analog A0.
#La seconde commande echo configure ce GPIO pour la sortie. 
#La troisième commande echo connecte A0 à la puce ADC.
`echo -n "37" > /sys/class/gpio/export`
`echo -n "out" > /sys/class/gpio/gpio37/direction`
`echo -n "0" > /sys/class/gpio/gpio37/value`

while [ 1 ]
do
#La commande cat permet de récuperer la valeur
MESSAGE=$(cat /sys/bus/iio/devices/iio\:device0/in_voltage0_raw)

#Envoi du message sur le broker
`mosquitto_pub -h 169.254.152.66 -p 1884 -t co -m $MESSAGE`

#La commande sleep permet de temporiser
`sleep 1`
done
