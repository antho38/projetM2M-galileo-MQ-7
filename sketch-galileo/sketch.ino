int sensorValueA;
int sensorValueD;
int compteur;

void setup()
{
  system("telnetd -l /bin/sh");
  system("ifconfig eth0 169.254.1.1 netmask 255.255.0.0 up"); //adapter l’adresse ip et le masque
  system("route add default gw 169.254.1.2"); // le PC devient passerelle par défaut
  compteur = 0;
  Serial.begin(9600);      // sets the serial port to 9600
}

void loop()
{
  sensorValueA = analogRead(0);       // read analog input pin 0
  sensorValueD = digitalRead(0);       // read analog input pin 0
  Serial.print(compteur, DEC);
  Serial.print(" : ");
  Serial.print(sensorValueA, DEC);  // prints the value read
  Serial.print("  ");
  Serial.println(sensorValueD, DEC);  // prints the value read
  delay(500);                        // wait 100ms for next reading
  compteur++;
}
