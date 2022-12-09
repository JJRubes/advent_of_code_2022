if [[ $# != 1 ]]
then
	echo "Usage: ./day_script dayNumber"
	exit
fi

DAY="day_"$1
mkdir $DAY
touch $DAY"/example_input.txt"
touch $DAY"/input.txt"
touch $DAY"/"$DAY".cpp"
touch $DAY"/"$DAY"_part_2.cpp"
cp "day_1/Makefile" $DAY
