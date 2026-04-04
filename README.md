# 1. Описать структуру данных
### _Пример:_
```c++
// Date struct
typeof struct {
    int day;
    int month;
    int year;
} ProductDate;
// Product struct
typeof struct {
    int id;
    ProductDate date;
    char companyName[100];
    char productName[100];
    float productionCount;
    float exportCount;
    float percentOfExport;
} ProductInfo;

typeof struct {
    int count;
    ProductInfo items;
} products;
```

# 2. Написать функции работы с данными

### _Пример:_
```c++
int sum() {
    int result = a + b;
    return result;
}
```


Где-то в коде...
```c++
int main() {
    int result = sum();
    printf("%d", result);
    return 0;
}
```

Для того чтобы в консоль выводились русские символы - изменить кодировку на `Windows-1251`

### Создание меню

1. Загрузка данных из файла
2. Вывести таблицу с данными
3. Добавить запись
4. Изменить запись
5. Удалить запись
6. Вычислить и вывести статистику
7. Сохранить данные в csv файл
8. Выход

# 3. Описание функций
Функции описываются следующим образом:
```c++
/**
* @param params logic
* @return void
*/
void NameOfFunction(params);
```

### _Пример:_
```c++
void menuReadFromFile();
void menuPrintTable();
void menuAddRecord();
void menuUpdateRecord();
void menuDeleteRecord();
void menuCalcStatistics();
void menuSaveToFile();
```
