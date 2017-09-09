#git
all:

help:
	@+echo ""
	@+echo ""
	@+echo "*********************************Help GIT******************************************"
	@+echo ""
	@+echo "make clone"
	@+echo "		git clone https://github.com/lion037osx/convertWavToCode.git"
	@+echo "make push"
	@+echo "		git push https://github.com/lion037osx/convertWavToCode.git"
	@+echo "make pull"
	@+echo "		git pull https://github.com/lion037osx/convertWavToCode.git"
	@+echo "make commit"
	@+echo "		git commit -m \"update\""
	@+echo "make add"
	@+echo "		git add ."
	@+echo "		git commit - m \"update\""
	@+echo "		git push origin master"
	@+echo ""
	@+echo ""
	@+echo "		Copyrigth by Leo"
	@+echo ""
	@+echo ""

clone:
	git init
	git clone https://github.com/lion037osx/convertWavToCode.git

push:
	git add.
	git commit -m "update"
#	git push origin master 
	git push https://github.com/lion037osx/convertWavToCode.git

pull:
	git add .
	git commit -m "upgrade"
#	git pull origin master
	git pull git push https://github.com/lion037osx/convertWavToCode.git

commit:

	git commit -m "update"

add:

	git add .

status:
	git status
	git remote -v

merge:
	git merge


	#git remote -v


upgrade:
	git add .
	git commit -m "update"
	git push origin master
update:
	git pull --all

init:
	echo "# convertWavToCode" >> README.md
	git init
	git add README.md
	git commit -m "app qt convert wav to code"
	git remote add origin https://github.com/lion037osx/convertWavToCode.git
	git push -u origin master
	

