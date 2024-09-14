#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <iomanip>
using namespace std;

bool is_it_int(const string& str) {
    if (str.empty()) return false;
    int dot_count = 0;
    if (str[0] == '0' && str.size() > 1 && str[1] != '.') {
        return false;
    }
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '.') {
            dot_count++;
            if (dot_count > 1) return false;
        } else if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    long double sum;
    double term_balance[5] = {10000, 1000, 1000, 1000, 1.5}, user_balance[5] = {1000000, 0, 0, 0, 0};
    double rub_to_usd = 90, rub_to_euro = 95, usd_to_euro = 1.1, usd_to_btc = 45000, usd_to_usdt = 1;
    int answer = 0;
    string mas[5] = {"RUB", "USD", "USDT", "EURO", "BTC"};
    string allowed[5] = {"13", "0234", "1", "01", "1"};
    bool change_flag = 0;
    srand(time(0));
    cout << fixed << setprecision(2) << endl;

    while (answer == 0) {
        string request_from, request_to, number;
        int int_request_from, int_request_to;
        long double int_number;
        bool fl = 1;
        change_flag = 0;
        cout << endl << "Текущий курс:" << endl << "RUB / USD = " << rub_to_usd << endl;
        cout << "RUB / EURO = 1 / " << rub_to_euro << endl;
        cout << "USD / EURO = 1 / " << usd_to_euro << endl;
        cout << "USD / USDT = 1 / " << usd_to_usdt << endl;
        cout << "USD / BTC = 1 / " << usd_to_btc << endl;
        cout << "Для запуска программы с начала в любой момент введите 'заново'" << endl;
        cout << "Для завершения программы в любой момент введите 'закончить'" << endl << endl;
        cout << endl << "Ваш баланс:" << endl;
        for (int i = 0; i < 5; i++) {
            cout << user_balance[i] << " " << mas[i] << endl;
        }
        cout << endl << "Баланс терминала:" << endl;
        for (int i = 0; i < 5; i++) {
            cout << term_balance[i] << " " << mas[i] << endl;
        }
        cout << endl;
        while (fl != 0) {
            cout << "Какую валюту вы хотите обменять?" << endl << "1 - RUB" << endl << "2 - USD" << endl << "3 - USDT" << endl << "4 - EURO" << endl << "5 - BTC" << endl;
            cin >> request_from;
            if (request_from == "end") {
                answer = 1;
                break;
            } else if (request_from == "again") {
                answer = 2;
                cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl  << endl;
                break;
            } else {
                if (is_it_int(request_from) and request_from.length() == 1) {
                    if (request_from.length() == 1 and (stoi(request_from) <= 5) and (stoi(request_from) >= 1)) fl = 0;
                    else cout << "Неверный ввод, попробуйте ещё раз" << endl << endl;
                } else cout << "Неверный ввод, попробуйте ещё раз" << endl << endl;
            }
        }
        if (answer == 1) break;
        if (answer == 0) {
            int_request_from = stoi(request_from);
            fl = 1;
            while (fl != 0) {
                string str;
                cout << "На какую валюту вы хотите обменять " << mas[int_request_from - 1] <<"?" << endl;
                for (int i = 0; i < allowed[int_request_from - 1].length(); i++) {
                    str = allowed[int_request_from - 1];
                    cout << i + 1 << " - " << mas[str[i] - '0'] << endl;
                }
                cout << endl;
                cin >> request_to;
                if (request_to == "end") {
                    answer = 1;
                    break;
                } else if (request_to == "again") {
                    answer = 2;
                    cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                    break;
                } else {
                    if (is_it_int(request_to) and request_to.length() == 1) {
                        if (request_to.length() == 1 and (stoi(request_to) >= 1) and (stoi(request_to) <= allowed[int_request_from - 1].length())) fl = 0;
                        else cout << "Неверный ввод, попробуйте ещё раз" << endl << endl;
                    } else cout << "Неверный ввод, попробуйте ещё раз" << endl << endl;
                }
            }
            if (answer == 1) break;
            fl = 1;
            if (answer == 0) {
                int_request_to = stoi(request_to);
                while (fl != 0) {
                    cout << "Какую сумму " << mas[allowed[int_request_from - 1][int_request_to - 1] - '0'] << " вы хотите получить?" << endl;
                    cin >> number;
                    if (number == "end") {
                        answer = 1;
                        break;
                    } else if (number == "again") {
                        answer = 2;
                        cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                        break;
                    } else {
                        if (is_it_int(number) and number.length() <= 9 and number != "0") {
                            int_number = stod(number);
                            if (int_request_from == 1 and int_request_to == 1) {
                                sum = int_number * rub_to_usd;
                                if (user_balance[int_request_from - 1] >= sum) {
                                    if (term_balance[allowed[int_request_from - 1][int_request_to - 1] - '0'] >= int_number) {
                                        fl = 0;
                                    } else cout << "Недостаточно средств в терминале, введите сумму повторно" << endl << endl;
                                } else cout << "Недостаточно средств на балансе, введите сумму повторно" << endl << endl;
                            } else if (int_request_from == 1 and int_request_to == 2) {
                                sum = int_number * rub_to_euro;
                                if (user_balance[int_request_from - 1] >= sum) {
                                    if (term_balance[allowed[int_request_from - 1][int_request_to - 1] - '0'] >= int_number) {
                                        fl = 0;
                                    } else cout << "Недостаточно средств в терминале, введите сумму повторно" << endl << endl;
                                } else cout << "Недостаточно средств на балансе, введите сумму повторно" << endl << endl;
                            } else if (int_request_from == 2 and int_request_to == 1) {
                                sum = int_number / rub_to_usd;
                                if (user_balance[int_request_from - 1] >= sum) {
                                    if (term_balance[allowed[int_request_from - 1][int_request_to - 1] - '0'] >= int_number) {
                                        fl = 0;
                                    } else cout << "Недостаточно средств в терминале, введите сумму повторно" << endl << endl;
                                } else cout << "Недостаточно средств на балансе, введите сумму повторно" << endl << endl;
                            } else if (int_request_from == 2 and int_request_to == 2) {
                                sum = int_number * usd_to_usdt;
                                if (user_balance[int_request_from - 1] >= sum) {
                                    if (term_balance[allowed[int_request_from - 1][int_request_to - 1] - '0'] >= int_number) {
                                        fl = 0;
                                    } else cout << "Недостаточно средств в терминале, введите сумму повторно" << endl << endl;
                                } else cout << "Недостаточно средств на балансе, введите сумму повторно" << endl << endl;
                            } else if (int_request_from == 2 and int_request_to == 3) {
                                sum = int_number * usd_to_euro;
                                if (user_balance[int_request_from - 1] >= sum) {
                                    if (term_balance[allowed[int_request_from - 1][int_request_to - 1] - '0'] >= int_number) {
                                        fl = 0;
                                    } else cout << "Недостаточно средств в терминале, введите сумму повторно" << endl << endl;
                                } else cout << "Недостаточно средств на балансе, введите сумму повторно" << endl << endl;
                            } else if (int_request_from == 2 and int_request_to == 4) {
                                sum = int_number * usd_to_btc;
                                if (user_balance[int_request_from - 1] >= sum) {
                                    if (term_balance[allowed[int_request_from - 1][int_request_to - 1] - '0'] >= int_number) {
                                        fl = 0;
                                    } else cout << "Недостаточно средств в терминале, введите сумму повторно" << endl << endl;
                                } else cout << "Недостаточно средств на балансе, введите сумму повторно" << endl << endl;
                            } else if (int_request_from == 3 and int_request_to == 1) {
                                sum = int_number / usd_to_usdt;
                                if (user_balance[int_request_from - 1] >= sum) {
                                    if (term_balance[allowed[int_request_from - 1][int_request_to - 1] - '0'] >= int_number) {
                                        fl = 0;
                                    } else cout << "Недостаточно средств в терминале, введите сумму повторно" << endl << endl;
                                } else cout << "Недостаточно средств на балансе, введите сумму повторно" << endl << endl;
                            } else if (int_request_from == 4 and int_request_to == 1) {
                                sum = int_number / rub_to_euro;
                                if (user_balance[int_request_from - 1] >= sum) {
                                    if (term_balance[allowed[int_request_from - 1][int_request_to - 1] - '0'] >= int_number) {
                                        fl = 0;
                                    } else cout << "Недостаточно средств в терминале, введите сумму повторно" << endl << endl;
                                } else cout << "Недостаточно средств на балансе, введите сумму повторно" << endl << endl;
                            } else if (int_request_from == 4 and int_request_to == 2) {
                                sum = int_number / usd_to_euro;
                                if (user_balance[int_request_from - 1] >= sum) {
                                    if (term_balance[allowed[int_request_from - 1][int_request_to - 1] - '0'] >= int_number) {
                                        fl = 0;
                                    } else cout << "Недостаточно средств в терминале, введите сумму повторно" << endl << endl;
                                } else cout << "Недостаточно средств на балансе, введите сумму повторно" << endl << endl;
                            } else if (int_request_from == 5 and int_request_to == 1) {
                                sum = int_number / usd_to_btc;
                                if (user_balance[int_request_from - 1] >= sum) {
                                    if (term_balance[allowed[int_request_from - 1][int_request_to - 1] - '0'] >= int_number) {
                                        fl = 0;
                                    } else cout << "Недостаточно средств в терминале, введите сумму повторно" << endl << endl;
                                } else cout << "Недостаточно средств на балансе, введите сумму повторно" << endl << endl;
                            }
                            cout << "Вы хотите приобрести " << int_number << " " << mas[allowed[int_request_from - 1][int_request_to - 1] - '0'] << endl;
                            cout << "Стоимость: " << sum << " " << mas[int_request_from - 1] << endl;
                            cout << "Ваш баланс: " << user_balance[int_request_from - 1] << " " << mas[int_request_from - 1] << endl << endl;
                        } else cout << "Неверный ввод, попробуйте ещё раз" << endl  << endl;
                    }
                }
                if (answer == 1) break;
                if (answer == 0) {
                    fl = 1;
                    while (fl != 0) {
                        cout << "Подтвердите транзакцию:" << endl << "0 - Да, произвести обмен" << endl << "1 - Нет, отменить обмен" << endl;
                        string approvement;
                        cin >> approvement;
                        if (approvement == "end") {
                            answer = 1;
                            break;
                        } else if (approvement == "again") {
                            answer = 2;
                            cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl  << endl;
                            break;
                        } else if (approvement == "1") {
                            fl = 0;
                            break;
                        } else if (approvement == "0") {
                            user_balance[int_request_from - 1] -= sum;
                            term_balance[int_request_from - 1] += sum;
                            user_balance[allowed[int_request_from - 1][int_request_to - 1] - '0'] += int_number;
                            term_balance[allowed[int_request_from - 1][int_request_to - 1] - '0'] -= int_number;
                            cout << "Успешно!" << endl;
                            cout << endl << "Ваш баланс:" << endl;
                            for (int i = 0; i < 5; i++) {
                                cout << user_balance[i] << " " << mas[i] << endl;
                            } cout << endl;
                            change_flag = 1;
                            fl = 0;
                        } else cout << "Неверный ввод, повторите попытку" << endl << endl;
                    }
                    if (change_flag) {
                        double x;
                        x = (rand() % (101) - 50) * 0.001;
                        rub_to_usd *= 1 + x;
                        x = (rand() % (101) - 50) * 0.001;
                        rub_to_euro *= 1 + x;
                        x = (rand() % (101) - 50) * 0.001;
                        usd_to_euro *= 1 + x;
                        x = (rand() % (101) - 50) * 0.001;
                        usd_to_btc *= 1 + x;
                        x = (rand() % (101) - 50) * 0.001;
                        usd_to_usdt *= 1 + x;
                    }
                    fl = 1;
                    while (fl != 0) {
                        cout << endl << "Начать новый обмен:" << endl << "0 - Да" << endl << "1 - Нет" << endl;
                        string ans;
                        cin >> ans;
                        if (ans == "end") {
                            answer = 1;
                            break;
                        } else if (ans == "again") {
                            answer = 2;
                            cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl  << endl;
                            break;
                        } else if (ans == "1") {
                            answer = 1;
                            fl = 0;
                            break;
                        } else if (ans == "0") {
                            answer = 0;
                            fl = 0;
                        } else cout << "Неверный ввод, повторите попытку" << endl << endl;
                    }
                } else answer = 0;
            } else answer = 0;
        } else answer = 0;
    }

    cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "Всего хорошего!";
}
