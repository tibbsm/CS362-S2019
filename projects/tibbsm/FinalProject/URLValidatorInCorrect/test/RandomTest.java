import junit.framework.TestCase;

import java.util.Random;

public class RandomTest extends TestCase {

    ResultPair[] testUrlScheme =
    {
            new ResultPair("http://", true),
            new ResultPair("ftp://", true),
            new ResultPair("h3t://", false),
            new ResultPair("3ht://", false),
            new ResultPair("http:/", false),
            new ResultPair("http:", false),
            new ResultPair("http/", false),
            new ResultPair("htp://", false),
            new ResultPair("htps://", false),
            new ResultPair("", false)
    };

    ResultPair[] testUrlAuthority =
    {
            new ResultPair("www.google.com", true),
            new ResultPair("www.google.com.", true),
            new ResultPair("google.com", true),
            new ResultPair("go.au", true),
            new ResultPair("0.0.0.0", true),
            new ResultPair("255.255.255.255", true),
            new ResultPair("256.256.256.256", false),
            new ResultPair("255.com", true),
            new ResultPair("1.2.3.4.5", false),
            new ResultPair("1.2.3.4.", false),
            new ResultPair("1.2.3", false),
            new ResultPair(".1.2.3.4", false),
            new ResultPair("go.a", false),
            new ResultPair("go.a1a", false),
            new ResultPair("go.cc", true),
            new ResultPair("go.1aa", false),
            new ResultPair("aaa.", false),
            new ResultPair(".aaa", false),
            new ResultPair("aaa", false),
            new ResultPair("", false)
    };

    ResultPair[] testUrlPort =
    {
            new ResultPair(":80", true),
            new ResultPair(":65535", true), // max possible
            new ResultPair(":65536", false), // max possible +1
            new ResultPair(":0", true),
            new ResultPair("", true),
            new ResultPair(":-1", false),
            new ResultPair(":65636", false),
            new ResultPair(":999999999999999999", false),
            new ResultPair(":65a", false),
            new ResultPair(":abc", false),
            new ResultPair(":xyz", false),
            new ResultPair(":lmn", false)
    };

    ResultPair[] testPath =
    {
            new ResultPair("/test1", true),
            new ResultPair("/t123", true),
            new ResultPair("/$23", true),
            new ResultPair("/..", false),
            new ResultPair("/../", false),
            new ResultPair("/test1/", true),
            new ResultPair("", true),
            new ResultPair("/test1/file", true),
            new ResultPair("/..//file", false),
            new ResultPair("/test1//file", false),
            new ResultPair("/test1/wer/file", true),
            new ResultPair("/test1/lessons/file", true),
    };

    ResultPair[] testUrlQuery =
    {
            new ResultPair("?action=view", true),
            new ResultPair("?action=edit&mode=up", true),
            new ResultPair("?q=query+list", true),
            new ResultPair("ふ??q=query+list", false),
            new ResultPair("!q=query+listから", false),
            new ResultPair("//?q=query+list", false),
            new ResultPair("ろ;;q=query+list", false),
            new ResultPair("``q=query+list", false),
            new ResultPair("あ=query+list", false),
            new ResultPair("?true=true", true)
    };

    /**
     * RANDOM TESTS
     */

    public void testUrlsRandomly() {
        System.out.print("-- testUrlsRandomly() --\n\n");
        UrlValidator urlValidator = new UrlValidator();

        Random r = new Random(System.currentTimeMillis());

        int limit = 100000, count = 1, url, auth, port, path, query;

        for (int i = 0; i < limit; i++){
            String testUrl =    testUrlScheme[url = r.nextInt(testUrlScheme.length)].item +
                                testUrlAuthority[auth = r.nextInt(testUrlAuthority.length)].item +
                                testUrlPort[port = r.nextInt(testUrlPort.length)].item +
                                testPath[path = r.nextInt(testPath.length)].item +
                                testUrlQuery[query = r.nextInt(testUrlQuery.length)].item;

            boolean testValidity =  testUrlScheme[url].valid &&
                                    testUrlAuthority[auth].valid &&
                                    testUrlPort[port].valid &&
                                    testPath[path].valid &&
                                    testUrlQuery[query].valid;


            System.out.print(count + ") Testing url: " + testUrl +" - ");

            if (urlValidator.isValid(testUrl) == testValidity)
                System.out.print("PASSED!\n");
            else {
                System.out.print(urlValidator.isValid(testUrl) + " - " + testValidity + " - FAILED!\n");
            }

            if (testValidity)
                assertTrue(urlValidator.isValid(testUrl));
            else
                assertFalse(urlValidator.isValid(testUrl));

            count++;
        }
    }
}
