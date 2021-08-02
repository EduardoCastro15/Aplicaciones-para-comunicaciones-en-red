#!/bin/bash

#variables
ipTap=192.168.0.21
mask=255.255.255.0
ipTapBroadcast=192.168.0.254

#Crear tap
sudo tunctl -t tap0 -u eduardocastro
echo tap creada...
#Levantar y asignar  IP
sudo ifconfig tap0 $ipTap netmask $mask up
echo tap lista y configurada...
echo ip = $ipTap
echo mascara = $mask

#Agregar rutas a la tabla de ruteo
sudo ip route add 192.168.1.0/24 via $ipTapBroadcast dev tap0
sudo ip route add 192.168.2.0/24 via $ipTapBroadcast dev tap0
sudo ip route add 192.168.3.0/24 via $ipTapBroadcast dev tap0
sudo ip route add 192.168.4.0/24 via $ipTapBroadcast dev tap0
sudo ip route add 192.168.5.0/24 via $ipTapBroadcast dev tap0
sudo ip route add 192.168.6.0/24 via $ipTapBroadcast dev tap0
echo Rutas agregadas a la tabla de ruteo...
echo Fin del script.
