package zhanj.removekdigit;

public class App {

    public static String removeKdigits(String num, int k) {
        int total = num.length();
        int n = total - k;
        if (n < 1) {
            return "0";
        }
        char[] number = new char[n];

        int i = 0, j = 0;
        while (i < n && j < k+i) {
            // j ~ total-n+i
            int min = j;
            char minDigit = num.charAt(min);
            for (int m = j+1; m <= k+i; ++m) {
                if (num.charAt(m) < minDigit) {
                    min = m;
                    minDigit = num.charAt(m);
                }
            }
            j = min+1;
            number[i++] = num.charAt(min);
        }
        while (i < n) {
            number[i++] = num.charAt(j++);
        }
        for (i = 0; i < n-1; ++i) {
            if (number[i] != '0') {
                break;
            }
        }
        return new String(number, i, n-i);
    }

    public static void main(String[] args) {
        System.out.println(removeKdigits("1000200", 1));
    }
}
