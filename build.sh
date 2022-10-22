#1/bin/bash
echo "Evaluating g++ settings..."
# Assuming g++ binary exists
if [[ -f /usr/bin/g++ ]];
then
	echo "g++ is installed on your system."
	echo "Creating build directory..."
	# Create CMakeEasy binary and build folders
	if [[ -d bin ]]
		then
		echo "bin directory exists."
	else
		mkdir bin
		cd bin
		mkdir build
		pwd
		cd -
		echo "bin and build directory created."
	fi
	echo "Starting compile..."
	# Build and move files
	if [[ -f CMakeEasy ]]
	then
		echo "CMakeEasy has already been compiled!"
		echo "Starting recompile..."
		g++ -Wall -o CMakeEasy Main.cpp Explainer.cpp Manager.cpp
		mv CMakeEasy bin/build/
		echo "CMakeEasy debug build created at"
		pwd
		echo ""
		echo "Compile operation complete."
	else
	g++ -Wall -o CMakeEasy Main.cpp Explainer.cpp Manager.cpp
	mv CMakeEasy bin/build/
	echo "CMakeEAsy debug build created at"
	pwd
	echo ""
	echo "Compile operation complete."
	fi
else
	echo "g++ was not detected."
	echo "No further operations are possible."
	echo "Compile operation will terminate."
fi
