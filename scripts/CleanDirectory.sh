cd ../
sudo find . -name "*.gcov" -type f -delete
sudo find . -name "*.gcno" -type f -delete
sudo find . -name "*.gcda" -type f -delete
sudo find . -name "*.o" -type f -delete
sudo rm -R ./bin/ 
sudo rm -R ./tests/CodeCoverage/
sudo mkdir ./bin/ 
sudo chown user ./bin/ && sudo chgrp user ./bin/
sudo mkdir ./tests/CodeCoverage/
sudo chown user ./tests/CodeCoverage/ && sudo chgrp user ./tests/CodeCoverage/
cd ./scripts/