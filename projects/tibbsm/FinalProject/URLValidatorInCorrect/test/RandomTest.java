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

    String[] validSchemes = {"http://","https://","ftp://"};
    String[] validAuthorities = {"google.com", "cnn.com", "yahoo.com", "bing.com", "github.com", "bitbucket.com","jira.com","asana.com","nba.com","www.wikipedia.org", "aol.com", "example.com", "oregonstate.edu", "some.io"};
    String[] validPorts = {":0", ":1000", ":2000", ":3000", ":4000", ":5000", ":6000", ":7000", ":8000", ":9000", ":10000", ":11000", ":12000", ":13000", ":14000", ":15000",":16000",":17000", ":65535"};
    String[] validPaths = {"/test1", "/qwerwqer/tewerwqest", "/teweqrqwerst/tewqerst", "/s/t", "/wqer/dsf", "/gdf/234", "/1234/1234", "/3/3", "/po/ll", "/se/cret", "/ok/ok", "/coo/l", "/noi/ce" };
    String[] validQueries = {"?ewr=vew", "?q=r", "?qwe=e", "?qwer=c", "?2134=1", "?dfs=3", "?lh=sd", "?sadf=sadf", "?asdfsadf=asdf", "?adfs=ads", "?sadfadsf=asdfsa" };

    public void testBadChars() {

        String goodUrl = "";
        UrlValidator urlValidator = new UrlValidator();
        int counter = 1;

        for (int i = 0; i < validSchemes.length; i++) {
            for (int j = 0; j < validAuthorities.length; j++) {
                for (int k = 0; k < validPorts.length; k++) {
                    for (int l = 0; l < validPaths.length; l++) {
                        for (int m = 0; m < validQueries.length; m++) {
                            goodUrl = validSchemes[i] + validAuthorities[j] + validPorts[k] + validPaths[l] + validQueries[m];

                            // get random "badChar" i.e. a character in range 0 - 32
                            Random rand = new Random();
                            char badChar = (char)rand.nextInt(33);

                            // get random n for inserting badChar from 0 to goodUrl.length - 1
                            int n = rand.nextInt(goodUrl.length());

                            // make badUrl by inserting badChar somewhere in copy of goodUrl
                            String badUrl = goodUrl.substring(0, n) + badChar + goodUrl.substring(n);

                            System.out.print(counter+") testingBadChars()\nTesting url: " + badUrl +" - ");

                            // assertTrue(urlValidator.isValid(badUrl));
                            if (urlValidator.isValid(badUrl))
                                System.out.print("PASSED!\n");
                            else
                                System.out.print("FAILED!\n");
                            System.out.print("Ascii value = " + (int) badChar + ", char: " + badChar);
                            System.out.print("n = " + n + "\n");

                            assertFalse(urlValidator.isValid(badUrl));
                            counter++;

                        }
                    }
                }
            }
        }
    }
}
