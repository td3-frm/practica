## Cambiar tamaño de imagenes jpg o png dentro de directorio a 800x600. 
## convert es parte del paquete imagemagick
## Se ejecuta como:
## $ photo-resize.sh ./ruta/al/directorio
## ./ruta/al/directorio es la ruta absoluta o relativa al directorio en 
## el que están las fotos.

#!/bin/bash

## $1 contiene ./ruta/al/directorio
cd $1

for img in $(ls *.[jJ][pP][gG])

do
	echo "Convirtiendo $img en sm_$img"
	convert $img -resize 800x600 -quality 100 -auto-orient sm_$img
done


for img in $(ls *.[pP][nN][gG])

do
	echo "Convirtiendo $img en sm_$img"
	convert $img -resize 800x600 -quality 100 -auto-orient sm_$img
done

echo "Conversión finalizada!"
