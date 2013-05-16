for i in `ls test-in/ | grep in`; do
  echo "Testing test-in/$i";
  ./s265fmt3 test-in/$i > test-out/out${i:2}
  
  
  if diff test-out/out${i:2} test-correct/out${i:2} > /dev/null; then
    printf "  \e[32m Pass! \e[0m \n"
  else
    printf "  \e[31m Fail! \e[0m \n"
  fi
done