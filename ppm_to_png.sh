cd pngs
echo "Deleting olds pngs..."
rm *.png
echo "Deleting olds ppms..."
rm *.ppm
cd ../renders
cp *.ppm ../pngs
echo "Copying ppm to png folder."
cd ../pngs
convert *.ppm *.png
echo "Converting..."
cd ..
echo "Conversion Done ! :] "

rm README.md
touch README.md

files=`ls ./pngs/*.png`
names=`ls ./renders/*.ppm`
echo "# Raytracer" >> README.md
echo " " >> README.md
echo "Simple raytracer made in C++. Based on the book *"Raytracing in a weekend"*">> README.md
echo " " >> README.md

for file in $files
do
    echo "![$file]($file)" >> README.md
done
echo "Writing README.md done !"