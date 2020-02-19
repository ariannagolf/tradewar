# tradewar
A desktop financial application to help personal investments

## Main Features
Tradewar is a personal investment tool that aids investment decisions by providing a summary of the general performance of major stocks as well as a detailed examination of single stocks through charts, tables, and relevant news. Tradewar also provides an analysis of each stock.

Tradewar utilizes the IEX API to grab stock data.

## Configuration
### Libcurl
Download latest version of Libcurl 
https://curl.haxx.se/download.html

### Boost
Downlaod boost from the following 
https://www.boost.org

Add the copy path to the .pro file. Use the below INCLUDEPATH as an example
ex. INCLUDEPATH += /usr/local/Cellar/boost/1.68.0/include
/usr/local/Cellar/boost_1_69_0/boost/1.69.0/include

## Issues
If the program crashes and/or compiles incorrectly when you first open the project, close the program and restart it. When you reopen the project it should run normally.
Also, running the program consecutively many times may lead to delays. 
This is most likely a result of the handling of the API calls which is something I was unable to resolve.
To circumvent this issue, shut down the program and it should run faster again. 
See Screenshots folder to see how the application should look without issues.

## TODO
Fix Analysis Page bug where peers and news data is appended each time you view a new stock
Fix program crashes mentioned in ISSUES.
Test page has not been fully implemented. This has been commented it out.

Copyright (c) 2019, Arianna Groetsema
All rights reserved.
