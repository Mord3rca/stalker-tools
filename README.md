# Stalker Tools

A set of tools used for S.T.A.L.K.E.R.'s gamefile manipulation

## ltx-reader

Parse a S.T.A.L.K.E.R. LTX file and spit it out on stdout a ConfigParser.

The result can be parsed by Python with:

```python
from configparser import ConfigParser

ini = ConfigParser()
ini.read('/path/to/file')
```

### Limitation

For now, case sensitivity is an issue and depend of your filesystem ...
