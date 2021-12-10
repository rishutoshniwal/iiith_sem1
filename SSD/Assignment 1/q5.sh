mkdir temp_activity
cd temp_activity
touch temp{1..50}.txt

declare -i i=1
while [ $i -le 25 ]
do
  mv "temp"$i".txt" "temp"$i".md"
  i=$(($i + 1))
done

for i in *.md
do
    mv -- "$i" "${i%.md}_modified.md"
done;
for i in *.txt
do
    mv -- "$i" "${i%.txt}_modified.txt"
done;
zip txt_compressed.zip *.txt