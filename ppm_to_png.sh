cd pngs
rm *.png
echo "Deleting olds pngs..."
cd ../renders
cp *.ppm ../pngs
echo "Copying ppm to png folder."
cd ../pngs
convert *.ppm *.png
echo "Converting..."
cd ..
echo "Conversion Done ! :] "