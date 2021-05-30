#!/bin/bash

# echo -e "\n\n>>>======================\e[33mSTART TEST: \e[0m\e[1m\e[35m$1\e[0m =======================<<<"
result=`$2`
result_code=$?
# if [[ $result_code -eq 0 ]]
# then
#     echo -e "\e[32m\e[1mTEST PASSED\e[0m"
# else
#     echo -e "\e[31m\e[1mTEST FAILED\e[0m"
# fi
# echo -e TEST RESULT: "\n""$result"

echo -e -n "\e[33mTEST: \e[0m\e[1m\e[35m$1\e[0m [[ "
if [[ $result_code -eq 0 ]]
then
    echo -e -n "\e[32m\e[1mPASSED\e[0m"
else
    echo -e -n "\e[31m\e[1mFAILED\e[0m"
fi
echo -e " ]]"
if [[ !$result_code -eq 0 ]]
then
    echo -e TEST RESULT: "\n""$result"
fi
# echo -e TEST RESULT: "\n""$result"




