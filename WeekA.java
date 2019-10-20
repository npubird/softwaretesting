import java.lang.*;
import java.util.Scanner;;
public class WeekA {
	public static void main(String[] args) {
		int year = 0;
		int month = 0;
		int day = 0;
		Scanner scan = new Scanner(System.in);
		System.out.print("请输入日期（格式xxxx xx xx）：");
		year = scan.nextInt();
		month = scan.nextInt();
		day = scan.nextInt();
		int weekday = getWeekday(year, month, day);
		System.out.println("输入日期为：星期" + weekday);
	}
	//当返回值小于等于0时则函数执行失败 
	//0代表当year、month、day中有负数 
	//-1代表year大于10000（在此处应为4位数） 
	//-2代表month大于12 
	//-3 代表day超过当月最大天数
	public static int getWeekday(int year, int month, int day) {
		// 验证输入合法性
		int[] MonthDays = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (((year % 4 == 0) && (year % 100 != 0)) || year % 400 == 0) {
			MonthDays[1] = 29;
		}
		if (year < 0 || month < 0 || day < 0) {
			return 0;
		}
		if (year > 10000) {
			return -1;
		} else if (month > 12) {
			return -2;
		} else if (day > MonthDays[month - 1]) {
			return -3;
		}
		// 开始计算
		int totalDays = 0;
		for (int i = 1; i < year; i++) {
			if (((i % 4 == 0) && (i % 100 != 0)) || i % 400 == 0) {
				totalDays += 366;
			} else {
				totalDays += 365;
			}
		}
		for (int i = 1; i < month; i++) {
			if (i == 2) {
				if (((year % 4 == 0) && (year % 100 != 0)) || year % 400 == 0) {
					MonthDays[1] = 29;
				}
			}
			totalDays += MonthDays[i - 1];
		}
		totalDays += day;
		int tempDay = totalDays % 7;
		if (tempDay == 0) {
			tempDay = 7;
		}
		return tempDay;
	}
}
