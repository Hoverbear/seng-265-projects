for i in `ls tests/ | grep in`; do
  echo "Testing tests/$i";
  ./s265fmt.py tests/$i > results/out${i:2}
  
  
  if diff results/out${i:2} tests/out${i:2} > /dev/null; then
    printf "  \e[32m Pass! \e[0m \n"
  else
    printf "  \e[31m Fail! \e[0m \n"
  fi
done