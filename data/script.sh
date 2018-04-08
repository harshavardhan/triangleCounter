if [ -d "modified" ];then rm -r modified/; fi
mkdir modified
orig='original/'
for file in original/*; do
    python3 dataSetFormatter.py $file
done
