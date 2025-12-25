Translate Application
=====================
Translate is designed to convert the data format of a text file into another data format. Supported data formats include field separated values such as comma-separated values (CSV).

Data formats:

* comma-separated values (csv)
* tab-separated values (tsv)

The application is written in the C++ language for both Windows and Linux operating systems.

### translate

```
usage: translate (options)

options: -i <input file name>
         -j <input data format: csv|tsv>
         -o <output file name>
         -p <output data format: csv|tsv>
         -r report statistics
         -v display version
         -x verbose mode
         -? print this usage
```