if [ $# -eq 1 ]; then
	rm -f $1/*.class $1/*.o \
		$1/*.so  $1/*~  $1/*.out
else
	rm -f ./*.class ./*.o \
		./*.so  ./*~  ./*.out
fi
	
