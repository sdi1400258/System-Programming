#include <iostream>
#include <cstdlib>
#include <string>

#include "datecmp.h"

using namespace std;

void datecmp_test() {
    string d1, d2, d3;

    cout << "Type date1 like (DD-MM-YYYY) format " << endl;
    cin >> d1;

    cout << "Type date2 like (DD-MM-YYYY) format " << endl;
    cin >> d2;

    cout << "Enter Date3 like (DD-MM-YYYY) format" << endl;
    cin >> d3;

    string cmp;
    cmp = datecmp(d3, d1, d2);
    cout << cmp << endl;
}

int datecmp(string date3, string date1, string date2) {

    string day1, month1, year1, day2, month2, year2, day3, month3, year3;


    day1 = date1.substr(0, 2); // DD-MM-YYYY
    month1 = date1.substr(3, 2);
    year1 = date1.substr(6, 4);


    day2 = date2.substr(0, 2); // DD-MM-YYYY
    month2 = date2.substr(3, 2);
    year2 = date2.substr(6, 4);

    int flag = 0;

    if (day1 > "0" && day1 < "31" && month1 > "0" && month1 < "13" && day2 > "0" && day2 < "31" && month2 > "0" && month2 < "13") {
//        cout << "Date1 -> " << "Day : " << day1 << ", Month : " << month1 << ", Year : " << year1 << endl;
//        cout << "Date2 -> " << "Day : " << day2 << ", Month : " << month2 << ", Year : " << year2 << endl;

        if (year1 > year2) {
//            cout << date1 << " > " << date2 << endl;
            flag = 1;
        } else if (year2 > year1) {
//            cout << date2 << " > " << date1 << endl;
            flag = 2;
        } else if (year1 == year2) {
            if (month1 > month2) {
//                cout << date1 << " > " << date2 << endl;
                flag = 3;
            } else if (month2 > month1) {
//                cout << date2 << " > " << date1 << endl;
                flag = 4;
            } else if (month1 == month2) {
                if (day1 > day2) {
//                    cout << date1 << " > " << date2 << endl;
                    flag = 5;
                } else if (day2 > day1) {
//                    cout << date2 << " > " << date1 << endl;
                    flag = 6;
                } else if (day1 == day2) {
                    return true;
                }
            }
        }
    } else {
        cout << "Wrong date input " << endl;
        return false;
    }


    day3 = date3.substr(0, 2); // DD-MM-YYYY
    month3 = date3.substr(3, 2);
    year3 = date3.substr(6, 4);

    if (day3 > "0" && day3 < "31" && month3 > "0" && month3 < "13") {
        if (flag == 1) {
            if (year3 < year1 && year3 > year2) {
                return true;
            } else if (year3 == year1) {
                if (month1 > month3) {
                    return true;
                } else if (month1 == month3) {
                    if (day1 >= day3) {
                        return true;
                    } else if (day1 < day3) {
                        return false;
                    }
                } else if (month1 < month3) {
                    return false;
                }
            } else if (year3 == year2) {
                if (month2 > month3) {
                    return true;
                } else if (month2 == month3) {
                    if (day2 >= day3) {
                        return true;
                    } else if (day2 < day3) {
                        return false;
                    }
                } else if (month2 < month3) {
                    return false;
                }
            } else if (year3 > year1 || year3 < year2) {
                return false;
            }
        } else if (flag == 2) {
            if (year3 < year2 && year3 > year1) {
                return true;
            } else if (year3 == year2) {
                if (month2 > month3) {
                    return true;
                } else if (month2 == month3) {
                    if (day2 >= day3) {
                        return true;
                    } else if (day2 < day3) {
                        return false;
                    }
                } else if (month2 < month3) {
                    return false;
                }
            } else if (year3 == year1) {
                if (month1 > month3) {
                    return true;
                } else if (month1 == month3) {
                    if (day1 >= day3) {
                        return true;
                    } else if (day1 < day3) {
                        return false;
                    }
                } else if (month1 < month3) {
                    return false;
                }
            } else if (year3 > year2 || year3 < year1) {
                return false;
            }

        } else if (flag == 3) {
            if (year3 > year1 || year3 < year1) {
                return false;
            } else if (year3 == year1) {
                if (month3 < month1 && month3 > month2) {
                    return true;
                } else if (month3 > month1 || month3 < month2) {
                    return false;
                } else if (month3 == month1) {
                    if (day3 <= day1) {
                        return true;
                    } else if (day3 > day1) {
                        return false;
                    }
                } else if (month3 == month2) {
                    if (day3 >= day2) {
                        return true;
                    } else if (day3 < day2) {
                        return false;
                    }
                }
            }

        } else if (flag == 4) {
            if (year3 > year2 || year3 < year2) {
                return false;
            } else if (year3 == year2) {
                if (month3 < month2 && month3 > month1) {
                    return true;
                } else if (month3 > month2 || month3 < month1) {
                    return false;
                } else if (month3 == month2) {
                    if (day3 <= day2) {
                        return true;
                    } else if (day3 > day2) {
                        return false;
                    }
                } else if (month3 == month1) {
                    if (day3 >= day1) {
                        return true;
                    } else if (day3 < day1) {
                        return false;
                    }
                }
            }
        } else if (flag == 5) {
            if (year3 > year1 || year3 < year1) {
                return false;
            } else if (month3 > month1 || month3 < month1) {
                return false;
            } else if (year3 == year1 && month3 == month1) {
                if (day3 <= day1 && day3 > day2) {
                    return true;
                } else
                    return false;
            }

        } else if (flag == 6) {
            if (year3 > year2 || year3 < year2) {
                return false;
            } else if (month3 > month2 || month3 < month2) {
                return false;
            } else if (year3 == year2 && month3 == month2) {
                if (day3 <= day2 && day3 > day1) {
                    return true;
                } else
                    return false;
            }
        } else if (flag == 0) {
            cout << "Wrong date input " << endl;
            return false;
        }
    }

    return false;

}