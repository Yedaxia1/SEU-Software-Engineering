import java.lang.*;
import java.util.Scanner;;
public class WeekA {
	public static void main(String[] args) {
		int year = 0;
		int month = 0;
		int day = 0;
		Scanner scan = new Scanner(System.in);
		System.out.print("���������ڣ���ʽxxxx xx xx����");
		year = scan.nextInt();
		month = scan.nextInt();
		day = scan.nextInt();
		int weekday = getWeekday(year, month, day);
		System.out.println("��������Ϊ������" + weekday);
	}
	//������ֵС�ڵ���0ʱ����ִ��ʧ�� 
	//0����year��month��day���и��� 
	//-1����year����10000���ڴ˴�ӦΪ4λ���� 
	//-2����month����12 
	//-3 ����day���������������
	public static int getWeekday(int year, int month, int day) {
		// ��֤����Ϸ���
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
		// ��ʼ����
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
