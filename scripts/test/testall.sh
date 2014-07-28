echo "Executing test_cppnew_tiny_O3..."
./query_test.rb -t cppnew --dataset tiny --O3 #> test_cppnew_tiny_O3.txt
echo "Executing test_cppnew_tiny_del_O3..."
./query_test.rb -t cppnew --dataset tiny_del --O3 #> test_cppnew_tiny_del_O3.txt
echo "Executing test_cppnew_standard_O3..."
./query_test.rb -t cppnew --dataset standard --O3 #> test_cppnew_standard_O3.txt
echo "Executing test_cppnew_standard_del_O3..."
./query_test.rb -t cppnew --dataset standard_del --O3 #> test_cppnew_standard_del_O3.txt
echo "Executing test_cppnew_tiny_O2..."
./query_test.rb -t cppnew --dataset tiny --O2 #> test_cppnew_tiny_O2.txt
echo "Executing test_cppnew_tiny_del_O2..."
./query_test.rb -t cppnew --dataset tiny_del --O2 #> test_cppnew_tiny_del_O2.txt
echo "Executing test_cppnew_standard_O2..."
./query_test.rb -t cppnew --dataset standard --O2 #> test_cppnew_standard_O2.txt
echo "Executing test_cppnew_standard_del_O2..."
./query_test.rb -t cppnew --dataset standard_del --O2 #> test_cppnew_standard_del_O2.txt
echo "Executing test_cppnew_tiny_O1..."
./query_test.rb -t cppnew --dataset tiny --O1 #> test_cppnew_tiny_O1.txt
echo "Executing test_cppnew_tiny_del_O1..."
./query_test.rb -t cppnew --dataset tiny_del --O1 #> test_cppnew_tiny_del_O1.txt
echo "Executing test_cppnew_standard_O1..."
./query_test.rb -t cppnew --dataset standard --O1 #> test_cppnew_standard_O1.txt
echo "Executing test_cppnew_standard_del_O1..."
./query_test.rb -t cppnew --dataset standard_del --O1 #> test_cppnew_standard_del_O1.txt
echo "Executing test_cppnew_big_O3..."
./query_test.rb -t cppnew --dataset big --O3 #> test_cppnew_big_O3.txt
echo "Executing test_cppnew_big_del_O3..."
./query_test.rb -t cppnew --dataset big_del --O3 #> test_cppnew_big_del_O3.txt
./query_test.rb -t cppnew --dataset big_del --O3 tpch5
./query_test.rb -t cppnew --dataset big_del --O3 tpch17a
./query_test.rb -t cppnew --dataset big_del --O3 tpch18
./query_test.rb -t cppnew --dataset big_del --O3 tpch18a
./query_test.rb -t cppnew --dataset big_del --O3 tpch21
echo "Executing test_cppnew_big_O2..."
./query_test.rb -t cppnew --dataset big --O2 #> test_cppnew_big_O2.txt
./query_test.rb -t cppnew --dataset big --O2 tpch11
echo "Executing test_cppnew_big_del_O2..."
./query_test.rb -t cppnew --dataset big_del --O2 #> test_cppnew_big_del_O2.txt
./query_test.rb -t cppnew --dataset big_del --O2 ssb4
echo "Executing test_cppnew_big_O1..."
./query_test.rb -t cppnew --dataset big --O1 #> test_cppnew_big_O1.txt
./query_test.rb -t cppnew --dataset big --O2 tpch11
echo "Executing test_cppnew_big_del_O1..."
./query_test.rb -t cppnew --dataset big_del --O1 #> test_cppnew_big_del_O1.txt
./query_test.rb -t cppnew --dataset big_del --O1 tpch18a
./query_test.rb -t cppnew --dataset big_del --O1 ssb4
