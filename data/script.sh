if [ -d "modified" ];then rm -r modified/; fi
mkdir modified
for file in original/*; do
	y="original/readme.txt"
	start=":start"
	end=":end"
	if [ $file != $y ]
	then
		echo $file$start
		python3 dataSetFormatter.py $file
		echo $file$end
	fi
done
touch modified/readme.txt
echo "This directory contains modified datasets after passing data to dataSetFormatter.py" > modified/readme.txt
