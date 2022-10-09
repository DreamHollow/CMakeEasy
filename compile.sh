#1/bin/bash
echo "Evaluating g++ settings..."
if [[ -f /usr/bin/g++ ]];
then
	echo "g++ is installed on your system."
	echo "Starting compile..."
	if [[ -f CMakeEasy ]]
	then
		echo "CMakeEasy has already been compiled!"
		echo "Starting recompile..."
		g++ -o CMakeEasy Main.cpp Explainer.cpp Manager.cpp
		echo "Compile operation complete."
	else
	g++ -o CMakeEasy Main.cpp Explainer.cpp Manager.cpp
	echo "Compile operation complete."
	fi
else
	echo "g++ was not detected."
	echo "Compile operation will terminate."
fi
