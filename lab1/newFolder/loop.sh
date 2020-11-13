for i in {2..50..2}
do
    if [ $i -lt 10 ]
    then
        echo -n "COE18B00$i";
    else
        echo -n "COE18I0$i";
    fi
    echo;
done
