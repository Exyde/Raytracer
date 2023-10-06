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

rm preview.md
touch preview.md

files=`ls ./pngs/*.png`
for file in $files
do
    echo $file
    echo "[$file]($file)" >> preview.md 
done
echo "Writing preview file done !"