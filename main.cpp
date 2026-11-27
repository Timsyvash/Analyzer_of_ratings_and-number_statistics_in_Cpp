#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

void clearInput() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readIntInRange(const string& prompt, int min_val, int max_val) {
  int value;
  cout << prompt;
  while (!(cin >> value) || value < min_val || value > max_val) {
    cout << "Помилка! Введіть ціле число від " << min_val << " до " << max_val << ": ";
    clearInput();
  }
  return value;
}

double readDouble(const string& prompt) {
  double value;
  cout << prompt;
  while (!(cin >> value)) {
    cout << "Помилка! Введіть коректне число: ";
    clearInput();
  }
  return value;
}

double calculateMedian(const vector<double>& sorted_nums) {
  size_t n = sorted_nums.size();
  if (n % 2 == 1) {
    return sorted_nums[n / 2];
  }
  return (sorted_nums[n / 2 - 1] + sorted_nums[n / 2]) / 2.0;
}

vector<double> findModes(const vector<double>& sorted_nums, int& max_frequency) {
  max_frequency = 0;
  vector<double> modes;

  if (sorted_nums.empty()) {
    return modes;
  }

  int current_count = 1;
  max_frequency = 1;

  for (size_t i = 1; i < sorted_nums.size(); ++i) {
    if (sorted_nums[i] == sorted_nums[i - 1]) {
      ++current_count;
    } else {
      if (current_count > max_frequency) {
        max_frequency = current_count;
      }
      current_count = 1;
    }
  }
  if (current_count > max_frequency) {
    max_frequency = current_count;
  }

  // Якщо жодне число не повторюється (усі зустрічаються по 1 разу), моди немає
  if (max_frequency <= 1) {
    return modes;
  }

  current_count = 1;
  for (size_t i = 1; i <= sorted_nums.size(); ++i) {
    if (i < sorted_nums.size() && sorted_nums[i] == sorted_nums[i - 1]) {
      ++current_count;
    } else {
      if (current_count == max_frequency) {
        modes.push_back(sorted_nums[i - 1]);
      }
      current_count = 1;
    }
  }

  return modes;
}

string getGradeLevel12(double avg) {
  if (avg >= 10.0 && avg <= 12.0) return "Високий рівень (10-12)";
  if (avg >= 7.0 && avg < 10.0)   return "Достатній рівень (7-9)";
  if (avg >= 4.0 && avg < 7.0)    return "Середній рівень (4-6)";
  if (avg >= 1.0 && avg < 4.0)    return "Початковий рівень (1-3)";
  return "Поза межами 12-бальної шкали";
}

void printStats(const vector<double>& numbers) {
  if (numbers.empty()) {
    cout << "Немає даних для аналізу.\n";
    return;
  }

  double sum = accumulate(numbers.begin(), numbers.end(), 0.0);
  double avg = sum / static_cast<double>(numbers.size());

  auto min_it = min_element(numbers.begin(), numbers.end());
  auto max_it = max_element(numbers.begin(), numbers.end());

  int above_avg = 0;
  int below_avg = 0;
  int equal_avg = 0;

  for (double num : numbers) {
    if (num > avg) ++above_avg;
    else if (num < avg) ++below_avg;
    else ++equal_avg;
  }

  vector<double> sorted_nums = numbers;
  sort(sorted_nums.begin(), sorted_nums.end());
  double median = calculateMedian(sorted_nums);

  int max_freq = 0;
  vector<double> modes = findModes(sorted_nums, max_freq);

  cout << fixed << setprecision(2);
  cout << "\n=== Розширені результати аналізу ===\n";
  cout << "Кількість елементів: " << numbers.size() << "\n";
  cout << "Сума: " << sum << "\n";
  cout << "Середнє значення: " << avg << "\n";
  cout << "Медіана: " << median << "\n";

  cout << "Мода: ";
  if (modes.empty()) {
    cout << "відсутня (усі числа зустрічаються по 1 разу)\n";
  } else {
    for (size_t i = 0; i < modes.size(); ++i) {
      cout << modes[i];
      if (i + 1 < modes.size()) cout << ", ";
    }
    cout << " (зустрічається " << max_freq << " раз(и))\n";
  }

  cout << "Орієнтир (12-бальна шкала): " << getGradeLevel12(avg) << "\n";
  cout << "Мінімум: " << *min_it << "\n";
  cout << "Максимум: " << *max_it << "\n";
  cout << "Вище середнього: " << above_avg << "\n";
  cout << "Нижче середнього: " << below_avg << "\n";
  cout << "Дорівнюють середньому: " << equal_avg << "\n";

  cout << "Відсортовані за зростанням: ";
  for (size_t i = 0; i < sorted_nums.size(); ++i) {
    cout << sorted_nums[i];
    if (i + 1 < sorted_nums.size()) cout << ", ";
  }
  cout << "\n";
}

int main() {
  cout << "=== Аналізатор оцінок та статистики чисел v2.1 ===\n";

  while (true) {
    int count = readIntInRange("\nСкільки чисел/оцінок хочете ввести (від 1 до 100)? ", 1, 100);
    vector<double> numbers;
    numbers.reserve(count);

    for (int i = 0; i < count; ++i) {
      double val = readDouble("Введіть число #" + to_string(i + 1) + ": ");
      numbers.push_back(val);
    }

    printStats(numbers);

    int again = readIntInRange("\nПроаналізувати ще один набір чисел? (1 - так, 0 - вихід): ", 0, 1);
    if (again == 0) {
      cout << "До зустрічі!\n";
      break;
    }
  }

  return 0;
}
