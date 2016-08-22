/*
 * The constructor of the HashMap works with jdk version 7.40 or later, 
 * but not with older versions.
 */

import java.util.HashMap;

class FailHashMap {

	public static void main(String[] args) {
		HashMap hm = new HashMap(10000000);
	}
}
