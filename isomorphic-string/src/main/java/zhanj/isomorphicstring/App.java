package zhanj.isomorphicstring;

import java.util.HashMap;
import java.util.Map;

public class App {

    public static boolean isIsomorphic(String s, String t) {
        Map<Character, Character> map1 = new HashMap<>(s.length());
        Map<Character, Character> map2 = new HashMap<>(t.length());
        for (int i = 0; i < s.length(); ++i) {
            char c1 = s.charAt(i);
            char c2 = t.charAt(i);
            Character m1 = map1.get(c1);
            Character m2 = map2.get(c2);
            if (m1 == null) {
                if (m2 == null) {
                    map1.put(c1, c2);
                    map2.put(c2, c1);
                    continue;
                }
            } else if (m2 != null) {
                if (m1 == c2 && m2 == c1) {
                    continue;
                }
            }
            return false;
        }
        return true;
    }

    public static boolean isIsomorphic2(String s, String t) {
        int[] map1 = new int[128];
        int[] map2 = new int[128];
        int i = 0;
        for ( ; i < s.length() && map1[s.charAt(i)] == map2[t.charAt(i)]; ++i) {
            map1[s.charAt(i)] = map2[t.charAt(i)] = i+1;
        }
        return i == s.length();
    }

    public static void main(String[] args) {
        String s = "dcc";
        String t = "axx";
        System.out.printf("'%s' - '%s'  %s%n", s, t, isIsomorphic(s, t));
        System.out.printf("'%s' - '%s'  %s%n", s, t, isIsomorphic2(s, t));
    }
}
