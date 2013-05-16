for i in `ls tests/ | grep in`; do
  echo "Testing tests/$i";
  ./s265fmt2.py tests/$i > results/out${i:2}
  
  
  if diff results/out${i:2} tests/out${i:2} > /dev/null; then
    printf "  \e[32m Pass! \e[0m \n"
  else
    printf "  \e[31m Fail! \e[0m \n"
  fi
done

printf "\n\e[32m--------------------------------------\e[0m \n\n"
printf "\e[31mERROR TESTING, using --strict, these should all fail: \e[0m \n"

for i in `ls error_tests/ | grep in`; do
  printf "\e[31mTesting error_tests/$i  \e[0m \n";
  ./s265fmt2.py --strict error_tests/$i > error_results/out${i:2}
done