## Scrip para fijar el tamaño de una imagen a 800x600. La funcion convert 
## es parte del paquete imagemagick

#!/bin/bash

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

dingdong

echo "Conversión de fotos finalizada!"

