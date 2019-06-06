import junit.framework.TestCase;

public class UnitTest extends TestCase {

    ResultPair[] testUrlScheme = {new ResultPair("http://", true),
            new ResultPair("ftp://", true),
            new ResultPair("h3t://", true),
            new ResultPair("3ht://", false),
            new ResultPair("http:/", false),
            new ResultPair("http:", false),
            new ResultPair("http/", false),
            new ResultPair("://", false)};

    ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
            new ResultPair("www.google.com.", true),
            new ResultPair("go.com", true),
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
    ResultPair[] testUrlPort = {new ResultPair(":80", true),
            new ResultPair(":65535", true), // max possible
            new ResultPair(":65536", false), // max possible +1
            new ResultPair(":0", true),
            new ResultPair("", true),
            new ResultPair(":-1", false),
            new ResultPair(":65636", false),
            new ResultPair(":999999999999999999", false),
            new ResultPair(":65a", false)
    };
    ResultPair[] testPath = {new ResultPair("/test1", true),
            new ResultPair("/t123", true),
            new ResultPair("/$23", true),
            new ResultPair("/..", false),
            new ResultPair("/../", false),
            new ResultPair("/test1/", true),
            new ResultPair("", true),
            new ResultPair("/test1/file", true),
            new ResultPair("/..//file", false),
            new ResultPair("/test1//file", false)
    };

    ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
            new ResultPair("?action=edit&mode=up", true),
            new ResultPair("", true)
    };

    /**
     * UNIT TESTS
     */

    public void testUnitTests() {
        // Testing valid urls (hardcoded)
        testValidUrl();

        // Testing invalid urls (hardcoded)
        testInvalidScheme();
        testInvalidAuthority();
        testInvalidPath();
        testInvalidPort();

        // Test valid urls (generated)
        testValidUrls();

        // Test invalid urls (generated)
        testInvalidUrls();

        // Misc Tests
        testUsername();
        testIPV6();
        testIPV4();
        testWithouPort();
        testEmpty();
    }

    /**
     * Test a valid url
     */
    public void testValidUrl() {
        UrlValidator urlValidator = new UrlValidator();

        String testUrl = testUrlScheme[0].item + testUrlAuthority[0].item + testUrlPort[0].item +
                testPath[0].item + testUrlQuery[0].item;

        System.out.print("\ntestValidUrl()\nTesting url: " + testUrl +" - ");

        if (urlValidator.isValid(testUrl))
            System.out.print("PASSED!\n");
        else
            System.out.print("FAILED!\n");

        assertTrue(urlValidator.isValid(testUrl));
    }

    /**
     * Test a valid scheme
     */
    public void testInvalidScheme() {
        UrlValidator urlValidator = new UrlValidator();

        String testUrl  =  testUrlScheme[4].item + testUrlAuthority[0].item + testUrlPort[0].item
                + testPath[0].item + testUrlQuery[0].item;

        System.out.print("\ntestInvalidScheme()\nTesting url: " + testUrl +" - ");

        if (!urlValidator.isValid(testUrl))
            System.out.print("PASSED!\n");
        else
            System.out.print("FAILED!\n");

        assertFalse(urlValidator.isValid(testUrl));
    }

    /**
     * Test a valid authority
     */
    public void testInvalidAuthority() {
        UrlValidator urlValidator = new UrlValidator();

        String testUrl  =  testUrlScheme[0].item + testUrlAuthority[6].item + testUrlPort[0].item
                + testPath[0].item + testUrlQuery[0].item;

        System.out.print("\ntestInvalidAuthority()\nTesting url: " + testUrl +" - ");

        if (!urlValidator.isValid(testUrl))
            System.out.print("PASSED!\n");
        else
            System.out.print("FAILED!\n");

        assertFalse(urlValidator.isValid(testUrl));
    }

    /**
     * Test a valid port
     */
    public void testInvalidPort() {
        UrlValidator urlValidator = new UrlValidator();

        String testUrl  =  testUrlScheme[0].item + testUrlAuthority[6].item + testUrlPort[2].item
                + testPath[0].item + testUrlQuery[0].item;

        System.out.print("\ntestInvalidPort()\nTesting url: " + testUrl +" - ");

        if (!urlValidator.isValid(testUrl))
            System.out.print("PASSED!\n");
        else
            System.out.print("FAILED!\n");

        assertFalse(urlValidator.isValid(testUrl));
    }

    /**
     * Test a valid path
     */
    public void testInvalidPath() {
        UrlValidator urlValidator = new UrlValidator();

        String testUrl  =  testUrlScheme[0].item + testUrlAuthority[6].item + testUrlPort[0].item
                + testPath[3].item + testUrlQuery[0].item;

        System.out.print("\ntestInvalidPath()\nTesting url: " + testUrl +" - ");

        if (!urlValidator.isValid(testUrl))
            System.out.print("PASSED!\n");
        else
            System.out.print("FAILED!\n");

        assertFalse(urlValidator.isValid(testUrl));
    }

    /**
     * Test a valid path
     */
    public void testInvalidQuery() {
        UrlValidator urlValidator = new UrlValidator();

        String testUrl  =  testUrlScheme[0].item + testUrlAuthority[6].item + testUrlPort[0].item
                + testPath[0].item + testUrlQuery[0].item;

        System.out.print("\ntestInvalidPath()\nTesting url: " + testUrl +" - ");

        if (!urlValidator.isValid(testUrl))
            System.out.print("PASSED!\n");
        else
            System.out.print("FAILED!\n");

        assertFalse(urlValidator.isValid(testUrl));
    }

    /**
     * Valid Urls
     *
     * Creates ~ 105,963 URLs
     */

    String[] validSchemes = {"http://","https://","ftp://"};
    String[] validAuthoritys = {"google.com", "cnn.com", "yahoo.com", "bing.com", "github.com", "bitbucket.com","jira.com","asana.com","nba.com","www.wikipedia.org", "aol.com", "example.com", "oregonstate.edu", "some.io"};
    String[] validPorts = {":0", ":1000", ":2000", ":3000", ":4000", ":5000", ":6000", ":7000", ":8000", ":9000", ":10000", ":11000", ":12000", ":13000", ":14000", ":15000",":16000",":17000", ":65535"};
    String[] validPath = {"/test1", "/qwerwqer/tewerwqest", "/teweqrqwerst/tewqerst", "/s/t", "/wqer/dsf", "/gdf/234", "/1234/1234", "/3/3", "/po/ll", "/se/cret", "/ok/ok", "/coo/l", "/noi/ce" };
    String[] validQuerys = {"?ewr=vew", "?q=r", "?qwe=e", "?qwer=c", "?2134=1", "?dfs=3", "?lh=sd", "?sadf=sadf", "?asdfsadf=asdf", "?adfs=ads", "?sadfadsf=asdfsa" };

    /**
     * Test valid urls
     */

    public void testValidUrls() {
        String testUrl = "";
        UrlValidator urlValidator = new UrlValidator();
        int counter = 1;

        for (int i = 0; i < validSchemes.length; i++) {
            for (int j = 0; j < validAuthoritys.length; j++) {
                for (int k = 0; k < validPorts.length; k++) {
                    for (int l = 0; l < validPath.length; l++) {
                        for (int m = 0; m < validQuerys.length; m++) {
                            testUrl = validSchemes[i] + validAuthoritys[j] + validPorts[k] + validPath[l] + validQuerys[m];

                            System.out.print(counter+") testValidUrls()\nTesting url: " + testUrl +" - ");

                            if (urlValidator.isValid(testUrl))
                                System.out.print("PASSED!\n");
                            else
                                System.out.print("FAILED!\n");

                            counter++;

                            assertTrue(urlValidator.isValid(testUrl));
                        }
                    }
                }
            }
        }
    }


    /**
     * Invalid Urls
     *
     * Creates ~ 190,190 URLs
     */

    String[] invalidSchemes = {"HTTP://","httpS://","wqerqwerp://","qw://",""};
    String[] invalidAuthoritys = {"123.123.3000", "1.1.", "", "***", "/*&^(&^(&", "3000.3000.3000.","false","$##%#%#%","!!!!","1+1=2", "?????", "/asdas", "sadaf", "fff"};
    String[] invalidPorts = {"/test1", "/qwerwqer/tewerwqest", "/teweqrqwerst/tewqerst", "/s/t", "/wqer/dsf", "/gdf/234", "/1234/1234", "/3/3", "/po/ll", "/se/cret", "/ok/ok", "/coo/l", "/noi/ce" };
    String[] invalidPath = {":0", ":1000", ":2000", ":3000", ":4000", ":5000", ":6000", ":7000", ":8000", ":9000", ":10000", ":11000", ":12000", ":13000", ":14000", ":15000",":16000",":17000", ":65535"};
    String[] invalidQuerys = {"!@?ewr=vew", "124r", "????", "123123", "()()", ":)", ":(", "OH_NO", "-__-", "WRONG", "QWERTY" };

    /**
     * Test valid urls
     */

    public void testInvalidUrls() {
        String testUrl = "";
        UrlValidator urlValidator = new UrlValidator();
        int counter = 1;

        for (int i = 0; i < invalidSchemes.length; i++) {
            for (int j = 0; j < invalidAuthoritys.length; j++) {
                for (int k = 0; k < invalidPorts.length; k++) {
                    for (int l = 0; l < invalidPath.length; l++) {
                        for (int m = 0; m < invalidQuerys.length; m++) {
                            testUrl = invalidSchemes[i] + invalidAuthoritys[j] + invalidPorts[k] + invalidPath[l] + invalidQuerys[m];

                            System.out.print(counter+") testValidUrls()\nTesting url: " + testUrl +" - ");

                            if (!urlValidator.isValid(testUrl))
                                System.out.print("PASSED!\n");
                            else
                                System.out.print("FAILED!\n");

                            counter++;

                            assertFalse(urlValidator.isValid(testUrl));
                        }
                    }
                }
            }
        }
    }

    /**
     *   Testing with a username (like tibbsm)
     *   Testing without a username
     *   Formatted as ipv6
     *   Formatted as ipv4
     *   Test with port
     *   Test without port
     *   Everything is empty
     */

    public void testUsername() {
        UrlValidator urlValidator = new UrlValidator();

        String testUrl  =  "http://user:@www.google.com:80/test/test";

        System.out.print("\ntestUsername()\nTesting url: " + testUrl +" - ");

        if (urlValidator.isValid(testUrl))
            System.out.print("PASSED!\n");
        else
            System.out.print("FAILED!\n");

        assertTrue(urlValidator.isValid(testUrl));
    }

    public void testIPV6() {
        UrlValidator urlValidator = new UrlValidator();

        String testUrl  =  "http://[FEDC:BA98:7654:3210:FEDC:BA98:7654:3210]:80/index.html";

        System.out.print("\ntestIPV6()\nTesting url: " + testUrl +" - ");

        if (urlValidator.isValid(testUrl))
            System.out.print("PASSED!\n");
        else
            System.out.print("FAILED!\n");

        assertTrue(urlValidator.isValid(testUrl));
    }

    public void testIPV4() {
        UrlValidator urlValidator = new UrlValidator();

        String testUrl  =  "http://255.255.255.255:80/";

        System.out.print("\ntestIPV4()\nTesting url: " + testUrl +" - ");

        if (urlValidator.isValid(testUrl))
            System.out.print("PASSED!\n");
        else
            System.out.print("FAILED!\n");

        assertTrue(urlValidator.isValid(testUrl));
    }

    public void testWithouPort() {
        UrlValidator urlValidator = new UrlValidator();

        String testUrl  =  testUrlScheme[0].item + testUrlAuthority[0].item + testPath[0].item + testUrlQuery[0].item;

        System.out.print("\ntestWithouPort()\nTesting url: " + testUrl +" - ");

        if (!urlValidator.isValid(testUrl))
            System.out.print("PASSED!\n");
        else
            System.out.print("FAILED!\n");

        assertTrue(urlValidator.isValid(testUrl));
    }

    public void testEmpty() {
        UrlValidator urlValidator = new UrlValidator();

        String testUrl  =  "";

        System.out.print("\ntestInvalidPath()\nTesting url: " + testUrl +" - ");

        if (!urlValidator.isValid(testUrl))
            System.out.print("PASSED!\n");
        else
            System.out.print("FAILED!\n");

        assertFalse(urlValidator.isValid(testUrl));
    }


}
