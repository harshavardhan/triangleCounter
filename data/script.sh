if [ -d "modified" ];then rm -r modified/; fi
mkdir modified
for file in original/*; do
	y="original/readme.txt"
	if [ $file != $y ]
	then
		python3 dataSetFormatter.py $file
	fi
done
touch modified/readme.txt
echo "This directory contains modified datasets after passing data to dataSetFormatter.py" > modified/readme.txt	