# Удалите старый build
cd /Users/dmitriy/Developing/cpp-crossplatform-app
rm -rf build

# Создайте новый build
mkdir build && cd build

# Сгенерируйте проект
cmake ..

# Соберите
cmake --build .

# Запустите приложения
./main_app
./gtest_test
./catch2_test