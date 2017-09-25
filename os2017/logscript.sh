#!/bin/bash

echo "Log script started"
#Сохраняем текущий каталог для абсолютной адресации .log файлов
startpath=$PWD



#Цикл принятия команд
while true 
do
	read command
	#Сохраняем выполенную команду в стиле shell и ее результат в 
	# .log файл
	echo "$USER@$PWD:$ $command\n">>$startpath/logLab.log
	$command >>$startpath/logLab.log
	echo >>$startpath/logLab.log
	
	#Сохраняем список команд в иной .log файл, для 
	# возможности воспроизвести их в таком же порядке, как в предыдущей сессии	
	echo "$command">>$startpath/logCom.log
	
	
done 
