 for JAVA_FILE in $(find . -name "*.cpp")
    do
        if [ "$(file $JAVA_FILE | grep -v GBK)" != "" ] ;then
           echo convert $JAVA_FILE
	    cp $JAVA_FILE $JAVA_FILE"_TEMP"
            iconv -f UTF-8 -t GBK $JAVA_FILE > $JAVA_FILE"2"
            		 cp $JAVA_FILE"2" $JAVA_FILE
           		 rm $JAVA_FILE"2"
        fi
    done
