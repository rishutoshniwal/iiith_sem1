#!/bin/bash


function roman()
{

   
   declare -a c
   declare -i i=0
   t=$1
 #  ans=""
   
   
   while [ $t -ne 0 ]
   do
        if [ $t -ge 1000 ]
        then
        #var1="M"
        #i=digit "\${var1}" t/1000 i c
         for((j=0;j<t/1000;j++))
         do
         c[i]='M'
         i=$(($i + 1))
         done
        t=$(($t % 1000))
        
        elif [ $t -ge 500 ]
        then
             if [ $t  -lt 900 ]
             then
                   #var1="D"
                   #i=digit "\${var1}" t/500 i c
                    for((j=0;j<t/500;j++))
                    do
                    c[i]='D'
                    i=$(($i + 1))
                     done
                   t=$(($t % 500))
             else
                   #var1="C"
                   #var2="M"
                   #i=sub_digit "\${var1}" "\${var2}" i c
                    c[i]='C'
                    i=$(($i + 1))
                    c[i]='M'
                    i=$(($i + 1))
                   t=$(($t % 100))
             fi
             
        elif [ $t -ge 100 ]
        then
             if [ $t  -lt 400 ]
             then
             #var1="C"
             #i=digit "\${var1}" t/100 i c
              for((j=0;j<t/100;j++))
               do
                 c[i]='C'
                 i=$(($i + 1))
                 done
              t=$(($t % 100))
             else
             #var1="C"
             #var2="D"
             #i=sub_digit "\${var1}" "\${var2}" i c 
              c[i]='C'
              i=$(($i + 1))
              c[i]='D'
              i=$(($i + 1))      
             t=$(($t % 100))
             fi
             
        elif [ $t -ge 50 ]
        then
             if [ $t  -lt 90 ]
             then
             #var1="L"
            # i=digit "\${var1}" t/50 i c
             for((j=0;j<t/50;j++))
              do
             c[i]='L'
              i=$(($i + 1))
             done
             t=$(($t % 50))
             else
            # var1="X"
             #var2="C"
             #i=sub_digit "\${var1}" "\${var2}" i c 
              c[i]='X'
              i=$(($i + 1))
              c[i]='C'
              i=$(($i + 1))              
             t=$(($t % 10))
             fi
             
             
        elif [ $t -ge 10 ]
        then
             if [ $t  -lt 40 ]
             then
             #var1="X"
             #i=digit "\${var1}" t/10 i c
              for((j=0;j<t/10;j++))
              do
              c[i]='X'
              i=$(($i + 1))
              done
             t=$(($t % 10))
             else
             #var1="X"
             #var2="L"
             #i=sub_digit "\${var1}" "\${var2}" i c  
              c[i]='X'
              i=$(($i + 1))
              c[i]='L'
              i=$(($i + 1))    
             t=$(($t % 10))
             fi
             
        elif [ $t -ge 5 ]
        then
             if [ $t  -lt 9 ]
             then
             #var1="V"
             #i=digit "\${var1}" t/5 i c
              for((j=0;j<t/5;j++))
                 do
                 c[i]='V'
                 i=$(($i + 1))
                  done
             t=$(($t % 5))
             else
            # var1="I"
            # var2="X"
             #i=sub_digit "\${var1}" "\${var2}" i c   
              c[i]='I'
             i=$(($i + 1))
             c[i]='X'
              i=$(($i + 1))    
             t=0
             fi
             
 
         elif [ $t -ge 1 ]
         then
             if [ $t  -lt 4 ]
             then
             #var1="I"
             #i=digit "\${var1}" t i c
              for((j=0;j<t;j++))
              do
             c[i]='I'
             i=$(($i + 1))
             done
             t=0
             else
             #var1="I"
             #var2="V"
             #i=sub_digit "\${var1}" "\${var2}"  i c       
              c[i]='I'
              i=$(($i + 1))
              c[i]='V'
             i=$(($i + 1))            
             t=0
             fi  
             
        else 
            x=0         
             
        fi     
             
   done
   
   #echo ${c[@]}
  
  p=0
  ans=""
  while [ $p -lt ${#c[@]} ]
  do
       ans+=${c[$p]}
        p=$(($p + 1))
    
  done
  echo $ans 
  
  #for i in "${c[@]}"
  #do
   #   echo $i | tr -d '\n'
  #done
}



#function digit(){
#   i=$3
#   for((j=0;j<$2;j++))
#   do
#       $4[$3]=$1
#      i=$(($i + 1))
#   done
#   
#   return i
#}



#function digitHelp(){
   
#   for((j=0;j<t/1000;j++))
#   do
#       c[i]=M
 #      i=$(($i + 1))
#   done
   
#   return i
#}


#function sub_digitHelp(){
    #  i=$3
 #    c[i]=C
  #   i=$(($i + 1))
   #  $c[i]=M
    # i=$(($i + 1))
     #return i
     
     
#}



#function sub_digit(){
 #     i=$3
  #   $4[i]=$1
   #  i=$(($i + 1))
    # $4[i]=$2
     #i=$(($i + 1))
  #   return i
     
     
#}

#echo "rishu"
if [[ "$#" -eq 1 ]]
then
roman $1
else
let sum=$1+$2
roman $sum
fi