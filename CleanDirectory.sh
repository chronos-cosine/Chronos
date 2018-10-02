sudo find . -name "*.gcov" -type f -delete
sudo find . -name "*.gcno" -type f -delete
sudo find . -name "*.gcda" -type f -delete
sudo find . -name "*.o" -type f -delete
sudo rm -R ./bin/
sudo rm -R ../bin/
