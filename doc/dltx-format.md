## DLTX Format

DLTX is a modified INI format used in STALKER configuration files.

### Extra feature compared to INI

#### Key definition

A key can be defined without a value assignation

```ini
[foo]
bizz
buzz =
```

In this case, **foo.bizz** and **foo.buzz** are correct and equal (= null).

#### Key modifier

A modifier can be applied to variables, which can be defined this way

```ini
<modifier>key< = value>
```

List of modifier:

* **!!**: Delete key

* **>**: Insert in list

* **<**: Remove from list

#### Section modifier

A section can be edited with via modifier, which can be defined this way:

```ini
<modifier>[section]
```

List of modifier:

* **!**: Override - Override section and error out if section is not previously defined

* **@**: Safe override - Override section or create it if not previously defined

* **!!**: Section deletion - Remove a section

#### Section inheritance

A section can inherit other section with the following syntax:
```ini
[section]<:inherited_section>
```

Multiple inheritance can be set by separating inherited section names by a ","

Example:

```ini
[foo]:bizz,buzz
```

In this example, section **foo** will inherit **bizz** and **buzz**

