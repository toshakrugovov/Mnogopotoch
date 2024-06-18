#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;
// Функция для слияния двух отсортированных частей массива
void merge(vector<int>& arr, int left, int mid, int right) {
    // Создаем временные векторы для хранения левой и правой частей массива
    vector<int> leftArr(mid - left + 1); // leftArr для хранения левой части
    vector<int> rightArr(right - mid);   // rightArr для хранения правой части

    // Копируем данные из исходного массива во временные векторы
    // Заполняем leftArr данными из arr[left] до arr[mid]
    for (int i = 0; i < leftArr.size(); ++i) {
        leftArr[i] = arr[left + i];
    }

    // Заполняем rightArr данными из arr[mid+1] до arr[right]
    for (int j = 0; j < rightArr.size(); ++j) {
        rightArr[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left; // Инициализируем индексы для leftArr, rightArr и основного массива arr

    // Сливаем два временных вектора leftArr и rightArr обратно в основной массив arr в отсортированном порядке
    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++]; // Если элемент из leftArr меньше или равен элементу из rightArr, копируем его в arr
        }
        else {
            arr[k++] = rightArr[j++]; // Иначе копируем элемент из rightArr в arr
        }
    }

    // Копируем оставшиеся элементы из leftArr (если они есть) в arr
    while (i < leftArr.size()) {
        arr[k++] = leftArr[i++];
    }

    // Копируем оставшиеся элементы из rightArr (если они есть) в arr
    while (j < rightArr.size()) {
        arr[k++] = rightArr[j++];
    }
}


// Функция сортировки слиянием для заданного диапазона массива
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Находим середину массива

        // Создаем потоки для сортировки левой и правой половин массива
        thread leftThread(mergeSort, ref(arr), left, mid);
        thread rightThread(mergeSort, ref(arr), mid + 1, right);

        // Ждем завершения выполнения потоков сортировки
        leftThread.join();
        rightThread.join();

        // Объединяем отсортированные части массива
        merge(arr, left, mid, right);
    }
}

// Функция-обертка для вызова сортировки в потоке
void sortArray(vector<int>& arr) {
    cout << "========\t" << "Сортировка стартовала\t======" << endl; // Выводим сообщение о начале сортировки
    mergeSort(arr, 0, arr.size() - 1); // Вызываем функцию сортировки слиянием
    cout << "Отсортированный массив: ";
    for (int num : arr) {
        cout << num << " "; // Выводим отсортированный массив
    }
    cout << endl;
    cout << "========\t" << "Сортировка завершилась\t======" << endl; // Выводим сообщение о завершении сортировки
}

int main() {
    setlocale(LC_ALL, "ru"); // Устанавливаем локаль для корректного отображения русского текста

    vector<int> numbers(10); // Создаем вектор для хранения 10 целых чисел

    cout << "Введите 10 целых чисел для сортировки:" << endl;
    for (int i = 0; i < 10; ++i) {
        cin >> numbers[i]; // Заполняем вектор числами, введенными пользователем
    }

    thread sortThread(sortArray, ref(numbers)); // Создаем поток для выполнения функции sortArray с аргументом numbers (ссылка на вектор)

    // В основном потоке выводим сообщения о его идентификаторе и номере итерации
    for (int i = 0; i < 10; ++i) {
        cout << "ID потока в main: " << this_thread::get_id() << ". Номер итерации " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(500)); // Задержка для наглядности
    }

    sortThread.join(); // Ждем завершения выполнения потока

    return 0; // Возвращаем 0 в качестве успешного завершения программы
}
