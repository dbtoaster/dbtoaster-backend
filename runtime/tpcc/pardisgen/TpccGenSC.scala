
package tpcc.sc
import ddbt.lib.store._
import scala.collection.mutable.{ArrayBuffer,Set}
import java.util.Date
 class SCExecutor 
{
  val x1494 = { x1466: SEntry3_III => {
      var x1467: Int = -889275714
      var x1468: Int = 0
      val x1469 = x1467
      val x1470 = x1469.^(2)
      val x1471 = x1467 = x1470
      val x1472 = x1467
      val x1473 = x1467
      val x1474 = x1473.>>>(16)
      val x1475 = x1472.^(x1474)
      val x1476 = x1467 = x1475
      val x1477 = x1467
      val x1478 = x1477.*(-2048144789)
      val x1479 = x1467 = x1478
      val x1480 = x1467
      val x1481 = x1467
      val x1482 = x1481.>>>(13)
      val x1483 = x1480.^(x1482)
      val x1484 = x1467 = x1483
      val x1485 = x1467
      val x1486 = x1485.*(-1028477387)
      val x1487 = x1467 = x1486
      val x1488 = x1467
      val x1489 = x1467
      val x1490 = x1489.>>>(16)
      val x1491 = x1488.^(x1490)
      val x1492 = x1467 = x1491
      val x1493 = x1467
      x1493
    }
  }
  val x1513 = { (x1495: SEntry3_III, x1496: SEntry3_III) => {
      val x1497 = x1495._1
      val x1498 = x1496._1
      val x1499 = x1497.==(-100)
      val x1501 = x1499.||({
        val x1500 = x1498.==(-100)
        x1500
      })
      val x1503 = x1501.||({
        val x1502 = x1497.==(x1498)
        x1502
      })
      val x1504 = x1495._2
      val x1505 = x1496._2
      val x1506 = x1504.==(-100)
      val x1508 = x1506.||({
        val x1507 = x1505.==(-100)
        x1507
      })
      val x1510 = x1508.||({
        val x1509 = x1504.==(x1505)
        x1509
      })
      val x1511 = x1503.&&({
        x1510
      })
      val x1512 = if(x1511) 
      {
        0
      }
      else
      {
        1
      }
      
      x1512
    }
  }
  val x1514 = EntryIdx.apply(x1494, x1513)
  val x1516 = Array.apply(x1514)
  val x1517 = new Store[SEntry3_III](1, x1516)
  val x484 = x1517.index(0, IList, false, -1)
  val x1548 = { x1520: SEntry8_IIIIITDS => {
      var x1521: Int = -889275714
      var x1522: Int = 0
      val x1523 = x1521
      val x1524 = x1523.^(2)
      val x1525 = x1521 = x1524
      val x1526 = x1521
      val x1527 = x1521
      val x1528 = x1527.>>>(16)
      val x1529 = x1526.^(x1528)
      val x1530 = x1521 = x1529
      val x1531 = x1521
      val x1532 = x1531.*(-2048144789)
      val x1533 = x1521 = x1532
      val x1534 = x1521
      val x1535 = x1521
      val x1536 = x1535.>>>(13)
      val x1537 = x1534.^(x1536)
      val x1538 = x1521 = x1537
      val x1539 = x1521
      val x1540 = x1539.*(-1028477387)
      val x1541 = x1521 = x1540
      val x1542 = x1521
      val x1543 = x1521
      val x1544 = x1543.>>>(16)
      val x1545 = x1542.^(x1544)
      val x1546 = x1521 = x1545
      val x1547 = x1521
      x1547
    }
  }
  val x1607 = { (x1549: SEntry8_IIIIITDS, x1550: SEntry8_IIIIITDS) => {
      val x1551 = x1549._1
      val x1552 = x1550._1
      val x1553 = x1551.==(-100)
      val x1555 = x1553.||({
        val x1554 = x1552.==(-100)
        x1554
      })
      val x1557 = x1555.||({
        val x1556 = x1551.==(x1552)
        x1556
      })
      val x1558 = x1549._2
      val x1559 = x1550._2
      val x1560 = x1558.==(-100)
      val x1562 = x1560.||({
        val x1561 = x1559.==(-100)
        x1561
      })
      val x1564 = x1562.||({
        val x1563 = x1558.==(x1559)
        x1563
      })
      val x1565 = x1549._3
      val x1566 = x1550._3
      val x1567 = x1565.==(-100)
      val x1569 = x1567.||({
        val x1568 = x1566.==(-100)
        x1568
      })
      val x1571 = x1569.||({
        val x1570 = x1565.==(x1566)
        x1570
      })
      val x1572 = x1549._4
      val x1573 = x1550._4
      val x1574 = x1572.==(-100)
      val x1576 = x1574.||({
        val x1575 = x1573.==(-100)
        x1575
      })
      val x1578 = x1576.||({
        val x1577 = x1572.==(x1573)
        x1577
      })
      val x1579 = x1549._5
      val x1580 = x1550._5
      val x1581 = x1579.==(-100)
      val x1583 = x1581.||({
        val x1582 = x1580.==(-100)
        x1582
      })
      val x1585 = x1583.||({
        val x1584 = x1579.==(x1580)
        x1584
      })
      val x1586 = x1549._6
      val x1587 = x1550._6
      val x1588 = x1586.==(null)
      val x1590 = x1588.||({
        val x1589 = x1587.==(null)
        x1589
      })
      val x1592 = x1590.||({
        val x1591 = x1586.==(x1587)
        x1591
      })
      val x1593 = x1549._7
      val x1594 = x1550._7
      val x1595 = x1593.==(-100.0)
      val x1597 = x1595.||({
        val x1596 = x1594.==(-100.0)
        x1596
      })
      val x1599 = x1597.||({
        val x1598 = x1593.==(x1594)
        x1598
      })
      val x1600 = x1557.&&({
        x1564
      })
      val x1601 = x1600.&&({
        x1571
      })
      val x1602 = x1601.&&({
        x1578
      })
      val x1603 = x1602.&&({
        x1585
      })
      val x1604 = x1603.&&({
        x1592
      })
      val x1605 = x1604.&&({
        x1599
      })
      val x1606 = if(x1605) 
      {
        0
      }
      else
      {
        1
      }
      
      x1606
    }
  }
  val x1608 = EntryIdx.apply(x1548, x1607)
  val x1610 = Array.apply(x1608)
  val x1611 = new Store[SEntry8_IIIIITDS](1, x1610)
  val x489 = x1611.index(0, IList, false, -1)
  val x1642 = { x1614: SEntry9_ISSSSSSDD => {
      var x1615: Int = -889275714
      var x1616: Int = 0
      val x1617 = x1615
      val x1618 = x1617.^(2)
      val x1619 = x1615 = x1618
      val x1620 = x1615
      val x1621 = x1615
      val x1622 = x1621.>>>(16)
      val x1623 = x1620.^(x1622)
      val x1624 = x1615 = x1623
      val x1625 = x1615
      val x1626 = x1625.*(-2048144789)
      val x1627 = x1615 = x1626
      val x1628 = x1615
      val x1629 = x1615
      val x1630 = x1629.>>>(13)
      val x1631 = x1628.^(x1630)
      val x1632 = x1615 = x1631
      val x1633 = x1615
      val x1634 = x1633.*(-1028477387)
      val x1635 = x1615 = x1634
      val x1636 = x1615
      val x1637 = x1615
      val x1638 = x1637.>>>(16)
      val x1639 = x1636.^(x1638)
      val x1640 = x1615 = x1639
      val x1641 = x1615
      x1641
    }
  }
  val x1709 = { (x1643: SEntry9_ISSSSSSDD, x1644: SEntry9_ISSSSSSDD) => {
      val x1645 = x1643._1
      val x1646 = x1644._1
      val x1647 = x1645.==(-100)
      val x1649 = x1647.||({
        val x1648 = x1646.==(-100)
        x1648
      })
      val x1651 = x1649.||({
        val x1650 = x1645.==(x1646)
        x1650
      })
      val x1652 = x1643._2
      val x1653 = x1644._2
      val x1654 = x1652.==("")
      val x1656 = x1654.||({
        val x1655 = x1653.==("")
        x1655
      })
      val x1658 = x1656.||({
        val x1657 = x1652.==(x1653)
        x1657
      })
      val x1659 = x1643._3
      val x1660 = x1644._3
      val x1661 = x1659.==("")
      val x1663 = x1661.||({
        val x1662 = x1660.==("")
        x1662
      })
      val x1665 = x1663.||({
        val x1664 = x1659.==(x1660)
        x1664
      })
      val x1666 = x1643._4
      val x1667 = x1644._4
      val x1668 = x1666.==("")
      val x1670 = x1668.||({
        val x1669 = x1667.==("")
        x1669
      })
      val x1672 = x1670.||({
        val x1671 = x1666.==(x1667)
        x1671
      })
      val x1673 = x1643._5
      val x1674 = x1644._5
      val x1675 = x1673.==("")
      val x1677 = x1675.||({
        val x1676 = x1674.==("")
        x1676
      })
      val x1679 = x1677.||({
        val x1678 = x1673.==(x1674)
        x1678
      })
      val x1680 = x1643._6
      val x1681 = x1644._6
      val x1682 = x1680.==("")
      val x1684 = x1682.||({
        val x1683 = x1681.==("")
        x1683
      })
      val x1686 = x1684.||({
        val x1685 = x1680.==(x1681)
        x1685
      })
      val x1687 = x1643._7
      val x1688 = x1644._7
      val x1689 = x1687.==("")
      val x1691 = x1689.||({
        val x1690 = x1688.==("")
        x1690
      })
      val x1693 = x1691.||({
        val x1692 = x1687.==(x1688)
        x1692
      })
      val x1694 = x1643._8
      val x1695 = x1644._8
      val x1696 = x1694.==(-100.0)
      val x1698 = x1696.||({
        val x1697 = x1695.==(-100.0)
        x1697
      })
      val x1700 = x1698.||({
        val x1699 = x1694.==(x1695)
        x1699
      })
      val x1701 = x1651.&&({
        x1658
      })
      val x1702 = x1701.&&({
        x1665
      })
      val x1703 = x1702.&&({
        x1672
      })
      val x1704 = x1703.&&({
        x1679
      })
      val x1705 = x1704.&&({
        x1686
      })
      val x1706 = x1705.&&({
        x1693
      })
      val x1707 = x1706.&&({
        x1700
      })
      val x1708 = if(x1707) 
      {
        0
      }
      else
      {
        1
      }
      
      x1708
    }
  }
  val x1710 = EntryIdx.apply(x1642, x1709)
  val x1712 = Array.apply(x1710)
  val x1713 = new Store[SEntry9_ISSSSSSDD](1, x1712)
  val x494 = x1713.index(0, IList, false, -1)
  val x1744 = { x1716: SEntry5_IISDS => {
      var x1717: Int = -889275714
      var x1718: Int = 0
      val x1719 = x1717
      val x1720 = x1719.^(2)
      val x1721 = x1717 = x1720
      val x1722 = x1717
      val x1723 = x1717
      val x1724 = x1723.>>>(16)
      val x1725 = x1722.^(x1724)
      val x1726 = x1717 = x1725
      val x1727 = x1717
      val x1728 = x1727.*(-2048144789)
      val x1729 = x1717 = x1728
      val x1730 = x1717
      val x1731 = x1717
      val x1732 = x1731.>>>(13)
      val x1733 = x1730.^(x1732)
      val x1734 = x1717 = x1733
      val x1735 = x1717
      val x1736 = x1735.*(-1028477387)
      val x1737 = x1717 = x1736
      val x1738 = x1717
      val x1739 = x1717
      val x1740 = x1739.>>>(16)
      val x1741 = x1738.^(x1740)
      val x1742 = x1717 = x1741
      val x1743 = x1717
      x1743
    }
  }
  val x1779 = { (x1745: SEntry5_IISDS, x1746: SEntry5_IISDS) => {
      val x1747 = x1745._1
      val x1748 = x1746._1
      val x1749 = x1747.==(-100)
      val x1751 = x1749.||({
        val x1750 = x1748.==(-100)
        x1750
      })
      val x1753 = x1751.||({
        val x1752 = x1747.==(x1748)
        x1752
      })
      val x1754 = x1745._2
      val x1755 = x1746._2
      val x1756 = x1754.==(-100)
      val x1758 = x1756.||({
        val x1757 = x1755.==(-100)
        x1757
      })
      val x1760 = x1758.||({
        val x1759 = x1754.==(x1755)
        x1759
      })
      val x1761 = x1745._3
      val x1762 = x1746._3
      val x1763 = x1761.==("")
      val x1765 = x1763.||({
        val x1764 = x1762.==("")
        x1764
      })
      val x1767 = x1765.||({
        val x1766 = x1761.==(x1762)
        x1766
      })
      val x1768 = x1745._4
      val x1769 = x1746._4
      val x1770 = x1768.==(-100.0)
      val x1772 = x1770.||({
        val x1771 = x1769.==(-100.0)
        x1771
      })
      val x1774 = x1772.||({
        val x1773 = x1768.==(x1769)
        x1773
      })
      val x1775 = x1753.&&({
        x1760
      })
      val x1776 = x1775.&&({
        x1767
      })
      val x1777 = x1776.&&({
        x1774
      })
      val x1778 = if(x1777) 
      {
        0
      }
      else
      {
        1
      }
      
      x1778
    }
  }
  val x1780 = EntryIdx.apply(x1744, x1779)
  val x1782 = Array.apply(x1780)
  val x1783 = new Store[SEntry5_IISDS](1, x1782)
  val x499 = x1783.index(0, IList, false, -1)
  val x1814 = { x1786: SEntry8_IIIITIIB => {
      var x1787: Int = -889275714
      var x1788: Int = 0
      val x1789 = x1787
      val x1790 = x1789.^(2)
      val x1791 = x1787 = x1790
      val x1792 = x1787
      val x1793 = x1787
      val x1794 = x1793.>>>(16)
      val x1795 = x1792.^(x1794)
      val x1796 = x1787 = x1795
      val x1797 = x1787
      val x1798 = x1797.*(-2048144789)
      val x1799 = x1787 = x1798
      val x1800 = x1787
      val x1801 = x1787
      val x1802 = x1801.>>>(13)
      val x1803 = x1800.^(x1802)
      val x1804 = x1787 = x1803
      val x1805 = x1787
      val x1806 = x1805.*(-1028477387)
      val x1807 = x1787 = x1806
      val x1808 = x1787
      val x1809 = x1787
      val x1810 = x1809.>>>(16)
      val x1811 = x1808.^(x1810)
      val x1812 = x1787 = x1811
      val x1813 = x1787
      x1813
    }
  }
  val x1873 = { (x1815: SEntry8_IIIITIIB, x1816: SEntry8_IIIITIIB) => {
      val x1817 = x1815._1
      val x1818 = x1816._1
      val x1819 = x1817.==(-100)
      val x1821 = x1819.||({
        val x1820 = x1818.==(-100)
        x1820
      })
      val x1823 = x1821.||({
        val x1822 = x1817.==(x1818)
        x1822
      })
      val x1824 = x1815._2
      val x1825 = x1816._2
      val x1826 = x1824.==(-100)
      val x1828 = x1826.||({
        val x1827 = x1825.==(-100)
        x1827
      })
      val x1830 = x1828.||({
        val x1829 = x1824.==(x1825)
        x1829
      })
      val x1831 = x1815._3
      val x1832 = x1816._3
      val x1833 = x1831.==(-100)
      val x1835 = x1833.||({
        val x1834 = x1832.==(-100)
        x1834
      })
      val x1837 = x1835.||({
        val x1836 = x1831.==(x1832)
        x1836
      })
      val x1838 = x1815._4
      val x1839 = x1816._4
      val x1840 = x1838.==(-100)
      val x1842 = x1840.||({
        val x1841 = x1839.==(-100)
        x1841
      })
      val x1844 = x1842.||({
        val x1843 = x1838.==(x1839)
        x1843
      })
      val x1845 = x1815._5
      val x1846 = x1816._5
      val x1847 = x1845.==(null)
      val x1849 = x1847.||({
        val x1848 = x1846.==(null)
        x1848
      })
      val x1851 = x1849.||({
        val x1850 = x1845.==(x1846)
        x1850
      })
      val x1852 = x1815._6
      val x1853 = x1816._6
      val x1854 = x1852.==(-100)
      val x1856 = x1854.||({
        val x1855 = x1853.==(-100)
        x1855
      })
      val x1858 = x1856.||({
        val x1857 = x1852.==(x1853)
        x1857
      })
      val x1859 = x1815._7
      val x1860 = x1816._7
      val x1861 = x1859.==(-100)
      val x1863 = x1861.||({
        val x1862 = x1860.==(-100)
        x1862
      })
      val x1865 = x1863.||({
        val x1864 = x1859.==(x1860)
        x1864
      })
      val x1866 = x1823.&&({
        x1830
      })
      val x1867 = x1866.&&({
        x1837
      })
      val x1868 = x1867.&&({
        x1844
      })
      val x1869 = x1868.&&({
        x1851
      })
      val x1870 = x1869.&&({
        x1858
      })
      val x1871 = x1870.&&({
        x1865
      })
      val x1872 = if(x1871) 
      {
        0
      }
      else
      {
        1
      }
      
      x1872
    }
  }
  val x1874 = EntryIdx.apply(x1814, x1873)
  val x1876 = Array.apply(x1874)
  val x1877 = new Store[SEntry8_IIIITIIB](1, x1876)
  val x504 = x1877.index(0, IList, false, -1)
  val x1908 = { x1880: SEntry11_IISSSSSSDDI => {
      var x1881: Int = -889275714
      var x1882: Int = 0
      val x1883 = x1881
      val x1884 = x1883.^(2)
      val x1885 = x1881 = x1884
      val x1886 = x1881
      val x1887 = x1881
      val x1888 = x1887.>>>(16)
      val x1889 = x1886.^(x1888)
      val x1890 = x1881 = x1889
      val x1891 = x1881
      val x1892 = x1891.*(-2048144789)
      val x1893 = x1881 = x1892
      val x1894 = x1881
      val x1895 = x1881
      val x1896 = x1895.>>>(13)
      val x1897 = x1894.^(x1896)
      val x1898 = x1881 = x1897
      val x1899 = x1881
      val x1900 = x1899.*(-1028477387)
      val x1901 = x1881 = x1900
      val x1902 = x1881
      val x1903 = x1881
      val x1904 = x1903.>>>(16)
      val x1905 = x1902.^(x1904)
      val x1906 = x1881 = x1905
      val x1907 = x1881
      x1907
    }
  }
  val x1991 = { (x1909: SEntry11_IISSSSSSDDI, x1910: SEntry11_IISSSSSSDDI) => {
      val x1911 = x1909._1
      val x1912 = x1910._1
      val x1913 = x1911.==(-100)
      val x1915 = x1913.||({
        val x1914 = x1912.==(-100)
        x1914
      })
      val x1917 = x1915.||({
        val x1916 = x1911.==(x1912)
        x1916
      })
      val x1918 = x1909._2
      val x1919 = x1910._2
      val x1920 = x1918.==(-100)
      val x1922 = x1920.||({
        val x1921 = x1919.==(-100)
        x1921
      })
      val x1924 = x1922.||({
        val x1923 = x1918.==(x1919)
        x1923
      })
      val x1925 = x1909._3
      val x1926 = x1910._3
      val x1927 = x1925.==("")
      val x1929 = x1927.||({
        val x1928 = x1926.==("")
        x1928
      })
      val x1931 = x1929.||({
        val x1930 = x1925.==(x1926)
        x1930
      })
      val x1932 = x1909._4
      val x1933 = x1910._4
      val x1934 = x1932.==("")
      val x1936 = x1934.||({
        val x1935 = x1933.==("")
        x1935
      })
      val x1938 = x1936.||({
        val x1937 = x1932.==(x1933)
        x1937
      })
      val x1939 = x1909._5
      val x1940 = x1910._5
      val x1941 = x1939.==("")
      val x1943 = x1941.||({
        val x1942 = x1940.==("")
        x1942
      })
      val x1945 = x1943.||({
        val x1944 = x1939.==(x1940)
        x1944
      })
      val x1946 = x1909._6
      val x1947 = x1910._6
      val x1948 = x1946.==("")
      val x1950 = x1948.||({
        val x1949 = x1947.==("")
        x1949
      })
      val x1952 = x1950.||({
        val x1951 = x1946.==(x1947)
        x1951
      })
      val x1953 = x1909._7
      val x1954 = x1910._7
      val x1955 = x1953.==("")
      val x1957 = x1955.||({
        val x1956 = x1954.==("")
        x1956
      })
      val x1959 = x1957.||({
        val x1958 = x1953.==(x1954)
        x1958
      })
      val x1960 = x1909._8
      val x1961 = x1910._8
      val x1962 = x1960.==("")
      val x1964 = x1962.||({
        val x1963 = x1961.==("")
        x1963
      })
      val x1966 = x1964.||({
        val x1965 = x1960.==(x1961)
        x1965
      })
      val x1967 = x1909._9
      val x1968 = x1910._9
      val x1969 = x1967.==(-100.0)
      val x1971 = x1969.||({
        val x1970 = x1968.==(-100.0)
        x1970
      })
      val x1973 = x1971.||({
        val x1972 = x1967.==(x1968)
        x1972
      })
      val x1974 = x1909._10
      val x1975 = x1910._10
      val x1976 = x1974.==(-100.0)
      val x1978 = x1976.||({
        val x1977 = x1975.==(-100.0)
        x1977
      })
      val x1980 = x1978.||({
        val x1979 = x1974.==(x1975)
        x1979
      })
      val x1981 = x1917.&&({
        x1924
      })
      val x1982 = x1981.&&({
        x1931
      })
      val x1983 = x1982.&&({
        x1938
      })
      val x1984 = x1983.&&({
        x1945
      })
      val x1985 = x1984.&&({
        x1952
      })
      val x1986 = x1985.&&({
        x1959
      })
      val x1987 = x1986.&&({
        x1966
      })
      val x1988 = x1987.&&({
        x1973
      })
      val x1989 = x1988.&&({
        x1980
      })
      val x1990 = if(x1989) 
      {
        0
      }
      else
      {
        1
      }
      
      x1990
    }
  }
  val x1992 = EntryIdx.apply(x1908, x1991)
  val x1994 = Array.apply(x1992)
  val x1995 = new Store[SEntry11_IISSSSSSDDI](1, x1994)
  val x509 = x1995.index(0, IList, false, -1)
  val x2026 = { x1998: SEntry10_IIIIIITIDS => {
      var x1999: Int = -889275714
      var x2000: Int = 0
      val x2001 = x1999
      val x2002 = x2001.^(2)
      val x2003 = x1999 = x2002
      val x2004 = x1999
      val x2005 = x1999
      val x2006 = x2005.>>>(16)
      val x2007 = x2004.^(x2006)
      val x2008 = x1999 = x2007
      val x2009 = x1999
      val x2010 = x2009.*(-2048144789)
      val x2011 = x1999 = x2010
      val x2012 = x1999
      val x2013 = x1999
      val x2014 = x2013.>>>(13)
      val x2015 = x2012.^(x2014)
      val x2016 = x1999 = x2015
      val x2017 = x1999
      val x2018 = x2017.*(-1028477387)
      val x2019 = x1999 = x2018
      val x2020 = x1999
      val x2021 = x1999
      val x2022 = x2021.>>>(16)
      val x2023 = x2020.^(x2022)
      val x2024 = x1999 = x2023
      val x2025 = x1999
      x2025
    }
  }
  val x2101 = { (x2027: SEntry10_IIIIIITIDS, x2028: SEntry10_IIIIIITIDS) => {
      val x2029 = x2027._1
      val x2030 = x2028._1
      val x2031 = x2029.==(-100)
      val x2033 = x2031.||({
        val x2032 = x2030.==(-100)
        x2032
      })
      val x2035 = x2033.||({
        val x2034 = x2029.==(x2030)
        x2034
      })
      val x2036 = x2027._2
      val x2037 = x2028._2
      val x2038 = x2036.==(-100)
      val x2040 = x2038.||({
        val x2039 = x2037.==(-100)
        x2039
      })
      val x2042 = x2040.||({
        val x2041 = x2036.==(x2037)
        x2041
      })
      val x2043 = x2027._3
      val x2044 = x2028._3
      val x2045 = x2043.==(-100)
      val x2047 = x2045.||({
        val x2046 = x2044.==(-100)
        x2046
      })
      val x2049 = x2047.||({
        val x2048 = x2043.==(x2044)
        x2048
      })
      val x2050 = x2027._4
      val x2051 = x2028._4
      val x2052 = x2050.==(-100)
      val x2054 = x2052.||({
        val x2053 = x2051.==(-100)
        x2053
      })
      val x2056 = x2054.||({
        val x2055 = x2050.==(x2051)
        x2055
      })
      val x2057 = x2027._5
      val x2058 = x2028._5
      val x2059 = x2057.==(-100)
      val x2061 = x2059.||({
        val x2060 = x2058.==(-100)
        x2060
      })
      val x2063 = x2061.||({
        val x2062 = x2057.==(x2058)
        x2062
      })
      val x2064 = x2027._6
      val x2065 = x2028._6
      val x2066 = x2064.==(-100)
      val x2068 = x2066.||({
        val x2067 = x2065.==(-100)
        x2067
      })
      val x2070 = x2068.||({
        val x2069 = x2064.==(x2065)
        x2069
      })
      val x2071 = x2027._7
      val x2072 = x2028._7
      val x2073 = x2071.==(null)
      val x2075 = x2073.||({
        val x2074 = x2072.==(null)
        x2074
      })
      val x2077 = x2075.||({
        val x2076 = x2071.==(x2072)
        x2076
      })
      val x2078 = x2027._8
      val x2079 = x2028._8
      val x2080 = x2078.==(-100)
      val x2082 = x2080.||({
        val x2081 = x2079.==(-100)
        x2081
      })
      val x2084 = x2082.||({
        val x2083 = x2078.==(x2079)
        x2083
      })
      val x2085 = x2027._9
      val x2086 = x2028._9
      val x2087 = x2085.==(-100.0)
      val x2089 = x2087.||({
        val x2088 = x2086.==(-100.0)
        x2088
      })
      val x2091 = x2089.||({
        val x2090 = x2085.==(x2086)
        x2090
      })
      val x2092 = x2035.&&({
        x2042
      })
      val x2093 = x2092.&&({
        x2049
      })
      val x2094 = x2093.&&({
        x2056
      })
      val x2095 = x2094.&&({
        x2063
      })
      val x2096 = x2095.&&({
        x2070
      })
      val x2097 = x2096.&&({
        x2077
      })
      val x2098 = x2097.&&({
        x2084
      })
      val x2099 = x2098.&&({
        x2091
      })
      val x2100 = if(x2099) 
      {
        0
      }
      else
      {
        1
      }
      
      x2100
    }
  }
  val x2102 = EntryIdx.apply(x2026, x2101)
  val x2104 = Array.apply(x2102)
  val x2105 = new Store[SEntry10_IIIIIITIDS](1, x2104)
  val x514 = x2105.index(0, IList, false, -1)
  val x2136 = { x2108: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
      var x2109: Int = -889275714
      var x2110: Int = 0
      val x2111 = x2109
      val x2112 = x2111.^(2)
      val x2113 = x2109 = x2112
      val x2114 = x2109
      val x2115 = x2109
      val x2116 = x2115.>>>(16)
      val x2117 = x2114.^(x2116)
      val x2118 = x2109 = x2117
      val x2119 = x2109
      val x2120 = x2119.*(-2048144789)
      val x2121 = x2109 = x2120
      val x2122 = x2109
      val x2123 = x2109
      val x2124 = x2123.>>>(13)
      val x2125 = x2122.^(x2124)
      val x2126 = x2109 = x2125
      val x2127 = x2109
      val x2128 = x2127.*(-1028477387)
      val x2129 = x2109 = x2128
      val x2130 = x2109
      val x2131 = x2109
      val x2132 = x2131.>>>(16)
      val x2133 = x2130.^(x2132)
      val x2134 = x2109 = x2133
      val x2135 = x2109
      x2135
    }
  }
  val x2299 = { (x2137: SEntry21_IIISSSSSSSSSTSDDDDIIS, x2138: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
      val x2139 = x2137._1
      val x2140 = x2138._1
      val x2141 = x2139.==(-100)
      val x2143 = x2141.||({
        val x2142 = x2140.==(-100)
        x2142
      })
      val x2145 = x2143.||({
        val x2144 = x2139.==(x2140)
        x2144
      })
      val x2146 = x2137._2
      val x2147 = x2138._2
      val x2148 = x2146.==(-100)
      val x2150 = x2148.||({
        val x2149 = x2147.==(-100)
        x2149
      })
      val x2152 = x2150.||({
        val x2151 = x2146.==(x2147)
        x2151
      })
      val x2153 = x2137._3
      val x2154 = x2138._3
      val x2155 = x2153.==(-100)
      val x2157 = x2155.||({
        val x2156 = x2154.==(-100)
        x2156
      })
      val x2159 = x2157.||({
        val x2158 = x2153.==(x2154)
        x2158
      })
      val x2160 = x2137._4
      val x2161 = x2138._4
      val x2162 = x2160.==("")
      val x2164 = x2162.||({
        val x2163 = x2161.==("")
        x2163
      })
      val x2166 = x2164.||({
        val x2165 = x2160.==(x2161)
        x2165
      })
      val x2167 = x2137._5
      val x2168 = x2138._5
      val x2169 = x2167.==("")
      val x2171 = x2169.||({
        val x2170 = x2168.==("")
        x2170
      })
      val x2173 = x2171.||({
        val x2172 = x2167.==(x2168)
        x2172
      })
      val x2174 = x2137._6
      val x2175 = x2138._6
      val x2176 = x2174.==("")
      val x2178 = x2176.||({
        val x2177 = x2175.==("")
        x2177
      })
      val x2180 = x2178.||({
        val x2179 = x2174.==(x2175)
        x2179
      })
      val x2181 = x2137._7
      val x2182 = x2138._7
      val x2183 = x2181.==("")
      val x2185 = x2183.||({
        val x2184 = x2182.==("")
        x2184
      })
      val x2187 = x2185.||({
        val x2186 = x2181.==(x2182)
        x2186
      })
      val x2188 = x2137._8
      val x2189 = x2138._8
      val x2190 = x2188.==("")
      val x2192 = x2190.||({
        val x2191 = x2189.==("")
        x2191
      })
      val x2194 = x2192.||({
        val x2193 = x2188.==(x2189)
        x2193
      })
      val x2195 = x2137._9
      val x2196 = x2138._9
      val x2197 = x2195.==("")
      val x2199 = x2197.||({
        val x2198 = x2196.==("")
        x2198
      })
      val x2201 = x2199.||({
        val x2200 = x2195.==(x2196)
        x2200
      })
      val x2202 = x2137._10
      val x2203 = x2138._10
      val x2204 = x2202.==("")
      val x2206 = x2204.||({
        val x2205 = x2203.==("")
        x2205
      })
      val x2208 = x2206.||({
        val x2207 = x2202.==(x2203)
        x2207
      })
      val x2209 = x2137._11
      val x2210 = x2138._11
      val x2211 = x2209.==("")
      val x2213 = x2211.||({
        val x2212 = x2210.==("")
        x2212
      })
      val x2215 = x2213.||({
        val x2214 = x2209.==(x2210)
        x2214
      })
      val x2216 = x2137._12
      val x2217 = x2138._12
      val x2218 = x2216.==("")
      val x2220 = x2218.||({
        val x2219 = x2217.==("")
        x2219
      })
      val x2222 = x2220.||({
        val x2221 = x2216.==(x2217)
        x2221
      })
      val x2223 = x2137._13
      val x2224 = x2138._13
      val x2225 = x2223.==(null)
      val x2227 = x2225.||({
        val x2226 = x2224.==(null)
        x2226
      })
      val x2229 = x2227.||({
        val x2228 = x2223.==(x2224)
        x2228
      })
      val x2230 = x2137._14
      val x2231 = x2138._14
      val x2232 = x2230.==("")
      val x2234 = x2232.||({
        val x2233 = x2231.==("")
        x2233
      })
      val x2236 = x2234.||({
        val x2235 = x2230.==(x2231)
        x2235
      })
      val x2237 = x2137._15
      val x2238 = x2138._15
      val x2239 = x2237.==(-100.0)
      val x2241 = x2239.||({
        val x2240 = x2238.==(-100.0)
        x2240
      })
      val x2243 = x2241.||({
        val x2242 = x2237.==(x2238)
        x2242
      })
      val x2244 = x2137._16
      val x2245 = x2138._16
      val x2246 = x2244.==(-100.0)
      val x2248 = x2246.||({
        val x2247 = x2245.==(-100.0)
        x2247
      })
      val x2250 = x2248.||({
        val x2249 = x2244.==(x2245)
        x2249
      })
      val x2251 = x2137._17
      val x2252 = x2138._17
      val x2253 = x2251.==(-100.0)
      val x2255 = x2253.||({
        val x2254 = x2252.==(-100.0)
        x2254
      })
      val x2257 = x2255.||({
        val x2256 = x2251.==(x2252)
        x2256
      })
      val x2258 = x2137._18
      val x2259 = x2138._18
      val x2260 = x2258.==(-100.0)
      val x2262 = x2260.||({
        val x2261 = x2259.==(-100.0)
        x2261
      })
      val x2264 = x2262.||({
        val x2263 = x2258.==(x2259)
        x2263
      })
      val x2265 = x2137._19
      val x2266 = x2138._19
      val x2267 = x2265.==(-100)
      val x2269 = x2267.||({
        val x2268 = x2266.==(-100)
        x2268
      })
      val x2271 = x2269.||({
        val x2270 = x2265.==(x2266)
        x2270
      })
      val x2272 = x2137._20
      val x2273 = x2138._20
      val x2274 = x2272.==(-100)
      val x2276 = x2274.||({
        val x2275 = x2273.==(-100)
        x2275
      })
      val x2278 = x2276.||({
        val x2277 = x2272.==(x2273)
        x2277
      })
      val x2279 = x2145.&&({
        x2152
      })
      val x2280 = x2279.&&({
        x2159
      })
      val x2281 = x2280.&&({
        x2166
      })
      val x2282 = x2281.&&({
        x2173
      })
      val x2283 = x2282.&&({
        x2180
      })
      val x2284 = x2283.&&({
        x2187
      })
      val x2285 = x2284.&&({
        x2194
      })
      val x2286 = x2285.&&({
        x2201
      })
      val x2287 = x2286.&&({
        x2208
      })
      val x2288 = x2287.&&({
        x2215
      })
      val x2289 = x2288.&&({
        x2222
      })
      val x2290 = x2289.&&({
        x2229
      })
      val x2291 = x2290.&&({
        x2236
      })
      val x2292 = x2291.&&({
        x2243
      })
      val x2293 = x2292.&&({
        x2250
      })
      val x2294 = x2293.&&({
        x2257
      })
      val x2295 = x2294.&&({
        x2264
      })
      val x2296 = x2295.&&({
        x2271
      })
      val x2297 = x2296.&&({
        x2278
      })
      val x2298 = if(x2297) 
      {
        0
      }
      else
      {
        1
      }
      
      x2298
    }
  }
  val x2300 = EntryIdx.apply(x2136, x2299)
  val x2302 = Array.apply(x2300)
  val x2303 = new Store[SEntry21_IIISSSSSSSSSTSDDDDIIS](1, x2302)
  val x519 = x2303.index(0, IList, false, -1)
  val x2334 = { x2306: SEntry17_IIISSSSSSSSSSIIIS => {
      var x2307: Int = -889275714
      var x2308: Int = 0
      val x2309 = x2307
      val x2310 = x2309.^(2)
      val x2311 = x2307 = x2310
      val x2312 = x2307
      val x2313 = x2307
      val x2314 = x2313.>>>(16)
      val x2315 = x2312.^(x2314)
      val x2316 = x2307 = x2315
      val x2317 = x2307
      val x2318 = x2317.*(-2048144789)
      val x2319 = x2307 = x2318
      val x2320 = x2307
      val x2321 = x2307
      val x2322 = x2321.>>>(13)
      val x2323 = x2320.^(x2322)
      val x2324 = x2307 = x2323
      val x2325 = x2307
      val x2326 = x2325.*(-1028477387)
      val x2327 = x2307 = x2326
      val x2328 = x2307
      val x2329 = x2307
      val x2330 = x2329.>>>(16)
      val x2331 = x2328.^(x2330)
      val x2332 = x2307 = x2331
      val x2333 = x2307
      x2333
    }
  }
  val x2465 = { (x2335: SEntry17_IIISSSSSSSSSSIIIS, x2336: SEntry17_IIISSSSSSSSSSIIIS) => {
      val x2337 = x2335._1
      val x2338 = x2336._1
      val x2339 = x2337.==(-100)
      val x2341 = x2339.||({
        val x2340 = x2338.==(-100)
        x2340
      })
      val x2343 = x2341.||({
        val x2342 = x2337.==(x2338)
        x2342
      })
      val x2344 = x2335._2
      val x2345 = x2336._2
      val x2346 = x2344.==(-100)
      val x2348 = x2346.||({
        val x2347 = x2345.==(-100)
        x2347
      })
      val x2350 = x2348.||({
        val x2349 = x2344.==(x2345)
        x2349
      })
      val x2351 = x2335._3
      val x2352 = x2336._3
      val x2353 = x2351.==(-100)
      val x2355 = x2353.||({
        val x2354 = x2352.==(-100)
        x2354
      })
      val x2357 = x2355.||({
        val x2356 = x2351.==(x2352)
        x2356
      })
      val x2358 = x2335._4
      val x2359 = x2336._4
      val x2360 = x2358.==("")
      val x2362 = x2360.||({
        val x2361 = x2359.==("")
        x2361
      })
      val x2364 = x2362.||({
        val x2363 = x2358.==(x2359)
        x2363
      })
      val x2365 = x2335._5
      val x2366 = x2336._5
      val x2367 = x2365.==("")
      val x2369 = x2367.||({
        val x2368 = x2366.==("")
        x2368
      })
      val x2371 = x2369.||({
        val x2370 = x2365.==(x2366)
        x2370
      })
      val x2372 = x2335._6
      val x2373 = x2336._6
      val x2374 = x2372.==("")
      val x2376 = x2374.||({
        val x2375 = x2373.==("")
        x2375
      })
      val x2378 = x2376.||({
        val x2377 = x2372.==(x2373)
        x2377
      })
      val x2379 = x2335._7
      val x2380 = x2336._7
      val x2381 = x2379.==("")
      val x2383 = x2381.||({
        val x2382 = x2380.==("")
        x2382
      })
      val x2385 = x2383.||({
        val x2384 = x2379.==(x2380)
        x2384
      })
      val x2386 = x2335._8
      val x2387 = x2336._8
      val x2388 = x2386.==("")
      val x2390 = x2388.||({
        val x2389 = x2387.==("")
        x2389
      })
      val x2392 = x2390.||({
        val x2391 = x2386.==(x2387)
        x2391
      })
      val x2393 = x2335._9
      val x2394 = x2336._9
      val x2395 = x2393.==("")
      val x2397 = x2395.||({
        val x2396 = x2394.==("")
        x2396
      })
      val x2399 = x2397.||({
        val x2398 = x2393.==(x2394)
        x2398
      })
      val x2400 = x2335._10
      val x2401 = x2336._10
      val x2402 = x2400.==("")
      val x2404 = x2402.||({
        val x2403 = x2401.==("")
        x2403
      })
      val x2406 = x2404.||({
        val x2405 = x2400.==(x2401)
        x2405
      })
      val x2407 = x2335._11
      val x2408 = x2336._11
      val x2409 = x2407.==("")
      val x2411 = x2409.||({
        val x2410 = x2408.==("")
        x2410
      })
      val x2413 = x2411.||({
        val x2412 = x2407.==(x2408)
        x2412
      })
      val x2414 = x2335._12
      val x2415 = x2336._12
      val x2416 = x2414.==("")
      val x2418 = x2416.||({
        val x2417 = x2415.==("")
        x2417
      })
      val x2420 = x2418.||({
        val x2419 = x2414.==(x2415)
        x2419
      })
      val x2421 = x2335._13
      val x2422 = x2336._13
      val x2423 = x2421.==("")
      val x2425 = x2423.||({
        val x2424 = x2422.==("")
        x2424
      })
      val x2427 = x2425.||({
        val x2426 = x2421.==(x2422)
        x2426
      })
      val x2428 = x2335._14
      val x2429 = x2336._14
      val x2430 = x2428.==(-100)
      val x2432 = x2430.||({
        val x2431 = x2429.==(-100)
        x2431
      })
      val x2434 = x2432.||({
        val x2433 = x2428.==(x2429)
        x2433
      })
      val x2435 = x2335._15
      val x2436 = x2336._15
      val x2437 = x2435.==(-100)
      val x2439 = x2437.||({
        val x2438 = x2436.==(-100)
        x2438
      })
      val x2441 = x2439.||({
        val x2440 = x2435.==(x2436)
        x2440
      })
      val x2442 = x2335._16
      val x2443 = x2336._16
      val x2444 = x2442.==(-100)
      val x2446 = x2444.||({
        val x2445 = x2443.==(-100)
        x2445
      })
      val x2448 = x2446.||({
        val x2447 = x2442.==(x2443)
        x2447
      })
      val x2449 = x2343.&&({
        x2350
      })
      val x2450 = x2449.&&({
        x2357
      })
      val x2451 = x2450.&&({
        x2364
      })
      val x2452 = x2451.&&({
        x2371
      })
      val x2453 = x2452.&&({
        x2378
      })
      val x2454 = x2453.&&({
        x2385
      })
      val x2455 = x2454.&&({
        x2392
      })
      val x2456 = x2455.&&({
        x2399
      })
      val x2457 = x2456.&&({
        x2406
      })
      val x2458 = x2457.&&({
        x2413
      })
      val x2459 = x2458.&&({
        x2420
      })
      val x2460 = x2459.&&({
        x2427
      })
      val x2461 = x2460.&&({
        x2434
      })
      val x2462 = x2461.&&({
        x2441
      })
      val x2463 = x2462.&&({
        x2448
      })
      val x2464 = if(x2463) 
      {
        0
      }
      else
      {
        1
      }
      
      x2464
    }
  }
  val x2466 = EntryIdx.apply(x2334, x2465)
  val x2468 = Array.apply(x2466)
  val x2469 = new Store[SEntry17_IIISSSSSSSSSSIIIS](1, x2468)
  val x524 = x2469.index(0, IList, false, -1)
  
  val newOrderTbl = x1517
  val historyTbl = x1611
  val warehouseTbl = x1713
  val itemTbl = x1783
  val orderTbl = x1877
  val districtTbl = x1995
  val orderLineTbl = x2105
  val customerTbl = x2303
  val stockTbl = x2469
  val newOrderTxInst = new NewOrderTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
}
      
case class SEntry5_IISDS(var _1: Int, var _2: Int, var _3: String, var _4: Double, var _5: String) extends Entry(5) {def copy = SEntry5_IISDS(_1, _2, _3, _4, _5) }
case class SEntry11_IISSSSSSDDI(var _1: Int, var _2: Int, var _3: String, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: Double, var _10: Double, var _11: Int) extends Entry(11) {def copy = SEntry11_IISSSSSSDDI(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) }
case class SEntry21_IIISSSSSSSSSTSDDDDIIS(var _1: Int, var _2: Int, var _3: Int, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: String, var _10: String, var _11: String, var _12: String, var _13: Date, var _14: String, var _15: Double, var _16: Double, var _17: Double, var _18: Double, var _19: Int, var _20: Int, var _21: String) extends Entry(21) {def copy = SEntry21_IIISSSSSSSSSTSDDDDIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21) }
case class SEntry8_IIIITIIB(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Date, var _6: Int, var _7: Int, var _8: Boolean) extends Entry(8) {def copy = SEntry8_IIIITIIB(_1, _2, _3, _4, _5, _6, _7, _8) }
case class SEntry3_III(var _1: Int, var _2: Int, var _3: Int) extends Entry(3) {def copy = SEntry3_III(_1, _2, _3) }
case class SEntry8_IIIIITDS(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Int, var _6: Date, var _7: Double, var _8: String) extends Entry(8) {def copy = SEntry8_IIIIITDS(_1, _2, _3, _4, _5, _6, _7, _8) }
case class SEntry17_IIISSSSSSSSSSIIIS(var _1: Int, var _2: Int, var _3: Int, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: String, var _10: String, var _11: String, var _12: String, var _13: String, var _14: Int, var _15: Int, var _16: Int, var _17: String) extends Entry(17) {def copy = SEntry17_IIISSSSSSSSSSIIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) }
case class SEntry10_IIIIIITIDS(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Int, var _6: Int, var _7: Date, var _8: Int, var _9: Double, var _10: String) extends Entry(10) {def copy = SEntry10_IIIIIITIDS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10) }
case class SEntry9_ISSSSSSDD(var _1: Int, var _2: String, var _3: String, var _4: String, var _5: String, var _6: String, var _7: String, var _8: Double, var _9: Double) extends Entry(9) {def copy = SEntry9_ISSSSSSDD(_1, _2, _3, _4, _5, _6, _7, _8, _9) }
class DeliveryTx(x1517: Store[SEntry3_III], x1611: Store[SEntry8_IIIIITDS], x1713: Store[SEntry9_ISSSSSSDD], x1783: Store[SEntry5_IISDS], x1877: Store[SEntry8_IIIITIIB], x1995: Store[SEntry11_IISSSSSSDDI], x2105: Store[SEntry10_IIIIIITIDS], x2303: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x2469: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int) => Int) {
def apply(x10: Boolean, x11: Date, x12: Int, x13: Int) = {
  val x14 = new Array[Int](10)
  var x15: Int = 1
  val x67 = while({
    val x16 = x15
    val x17 = x16.<=(10)
    x17
  })
  {
    val x20 = { x18: SEntry3_III => {
        val x3587 = x18._1
        x3587
      }
    }
    val x21 = Aggregator.min(x20)
    val x22 = x15
    val x3486 = SEntry3_III(-100, x22, x12)
    val x25 = x1517.slice(0, x3486, x21)
    val x26 = x21.result
    val x27 = x26.!=(null)
    val x63 = if(x27) 
    {
      val x3491 = x26._1
      val x29 = x15
      val x30 = x29.-(1)
      val x31 = x14.update(x30, x3491)
      val x32 = x1517.delete(x26)
      val x33 = x15
      val x3497 = SEntry8_IIIITIIB(x3491, x33, x12, -100, null, -100, -100, false)
      val x36 = x1877.get(0, x3497)
      val x3500 = x36._4
      val x3501 = x36._6_=(x13)
      val x39 = x1877.update(x36)
      var x40: Double = 0.0
      val x41 = x15
      val x3506 = SEntry10_IIIIIITIDS(x3491, x41, x12, -100, -100, -100, null, -100, -100.0, "")
      val x51 = { x44: SEntry10_IIIIIITIDS => {
          val x3614 = x44._7_=(x11)
          val x46 = x40
          val x3616 = x44._9
          val x48 = x46.+(x3616)
          val x49 = x40 = x48
          val x50 = x2105.update(x44)
          x50
        }
      }
      val x52 = x2105.slice(0, x3506, x51)
      val x53 = x15
      val x3510 = SEntry21_IIISSSSSSSSSTSDDDDIIS(x3500, x53, x12, "", "", "", "", "", "", "", "", "", null, "", -100.0, -100.0, -100.0, -100.0, -100, -100, "")
      val x55 = x2303.get(0, x3510)
      val x56 = x40
      val x3513 = x55._17
      val x3514 = x3513.+(x56)
      val x3515 = x55._17_=(x3514)
      val x3516 = x55._20
      val x3517 = x3516.+(1)
      val x3518 = x55._20_=(x3517)
      val x59 = x2303.update(x55)
      x59
    }
    else
    {
      val x60 = x15
      val x61 = x60.-(1)
      val x62 = x14.update(x61, 0)
      x62
    }
    
    val x64 = x15
    val x65 = x64.+(1)
    val x66 = x15 = x65
    x66
  }
  val x121 = if(x10) 
  {
    val x68 = "\n+---------------------------- DELIVERY ---------------------------+\n Date: ".+(x11)
    val x69 = x68.+("\n\n Warehouse: ")
    val x70 = x69.+(x12)
    val x71 = x70.+("\n Carrier:   ")
    val x72 = x71.+(x13)
    val x73 = x72.+("\n\n Delivered Orders\n")
    var x74: String = x73
    var x75: Int = 0
    var x76: Int = 1
    val x115 = while({
      val x77 = x76
      val x78 = x77.<=(10)
      x78
    })
    {
      val x79 = x76
      val x80 = x79.-(1)
      val x81 = x14.apply(x80)
      val x82 = x81.>=(0)
      val x111 = if(x82) 
      {
        val x83 = x74
        val x84 = x83.+("  District ")
        val x85 = x76
        val x86 = x85.<(10)
        val x87 = if(x86) 
        {
          " "
        }
        else
        {
          ""
        }
        
        val x88 = x84.+(x87)
        val x89 = x76
        val x90 = x88.+(x89)
        val x91 = x90.+(": Order number ")
        val x92 = x76
        val x93 = x92.-(1)
        val x94 = x14.apply(x93)
        val x95 = x91.+(x94)
        val x96 = x95.+(" was delivered.\n")
        val x97 = x74 = x96
        x97
      }
      else
      {
        val x98 = x74
        val x99 = x98.+("  District ")
        val x100 = x76
        val x101 = x100.<(10)
        val x102 = if(x101) 
        {
          " "
        }
        else
        {
          ""
        }
        
        val x103 = x99.+(x102)
        val x104 = x76
        val x105 = x103.+(x104)
        val x106 = x105.+(": No orders to be delivered.\n")
        val x107 = x74 = x106
        val x108 = x75
        val x109 = x108.+(1)
        val x110 = x75 = x109
        x110
      }
      
      val x112 = x76
      val x113 = x112.+(1)
      val x114 = x76 = x113
      x114
    }
    val x116 = x74
    val x117 = x116.+("+-----------------------------------------------------------------+\n\n")
    val x118 = x74 = x117
    val x119 = x74
    val x120 = println(x119)
    ()
  }
  else
  {
    ()
  }
  
  1
}
}
class StockLevelTx(x1517: Store[SEntry3_III], x1611: Store[SEntry8_IIIIITDS], x1713: Store[SEntry9_ISSSSSSDD], x1783: Store[SEntry5_IISDS], x1877: Store[SEntry8_IIIITIIB], x1995: Store[SEntry11_IISSSSSSDDI], x2105: Store[SEntry10_IIIIIITIDS], x2303: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x2469: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int) => Int) {
def apply(x122: Boolean, x123: Date, x124: Int, x125: Int, x126: Int, x127: Int) = {
  val x3804 = SEntry11_IISSSSSSDDI(x126, x125, "", "", "", "", "", "", -100.0, -100.0, -100)
  val x130 = x1995.get(0, x3804)
  val x3807 = x130._11
  val x132 = x3807.-(20)
  var x133: Int = x132
  val x134 = Set.apply[Int]()
  val x153 = while({
    val x135 = x133
    val x136 = x135.<(x3807)
    x136
  })
  {
    val x137 = x133
    val x3816 = SEntry10_IIIIIITIDS(x137, x126, x125, -100, -100, -100, null, -100, -100.0, "")
    val x148 = { x140: SEntry10_IIIIIITIDS => {
        val x3848 = x140._5
        val x3849 = SEntry17_IIISSSSSSSSSSIIIS(x3848, x125, -100, "", "", "", "", "", "", "", "", "", "", -100, -100, -100, "")
        val x143 = x2469.get(0, x3849)
        val x3851 = x143._3
        val x145 = x3851.<(x127)
        val x147 = if(x145) 
        {
          val x146 = x134.+=(x3848)
          ()
        }
        else
        {
          ()
        }
        
        x147
      }
    }
    val x149 = x2105.slice(0, x3816, x148)
    val x150 = x133
    val x151 = x150.+(1)
    val x152 = x133 = x151
    x152
  }
  val x154 = x134.size
  val x164 = if(x122) 
  {
    val x155 = "\n+-------------------------- STOCK-LEVEL --------------------------+\n Warehouse: ".+(x125)
    val x156 = x155.+("\n District:  ")
    val x157 = x156.+(x126)
    val x158 = x157.+("\n\n Stock Level Threshold: ")
    val x159 = x158.+(x127)
    val x160 = x159.+("\n Low Stock Count:       ")
    val x161 = x160.+(x154)
    val x162 = x161.+("\n+-----------------------------------------------------------------+\n\n")
    val x163 = println(x162)
    ()
  }
  else
  {
    ()
  }
  
  1
}
}
class OrderStatusTx(x1517: Store[SEntry3_III], x1611: Store[SEntry8_IIIIITDS], x1713: Store[SEntry9_ISSSSSSDD], x1783: Store[SEntry5_IISDS], x1877: Store[SEntry8_IIIITIIB], x1995: Store[SEntry11_IISSSSSSDDI], x2105: Store[SEntry10_IIIIIITIDS], x2303: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x2469: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int) {
def apply(x165: Boolean, x166: Date, x167: Int, x168: Int, x169: Int, x170: Int, x171: Int, x172: String) = {
  var x3907: SEntry21_IIISSSSSSSSSTSDDDDIIS = null
  val x174 = x170.>(0)
  val x207 = if(x174) 
  {
    val x3910 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
    val x3912 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-100, x169, x168, "", "", x172, "", "", "", "", "", "", null, "", -100.0, -100.0, -100.0, -100.0, -100, -100, "")
    val x180 = { x178: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
        val x179 = x3910.append(x178)
        x179
      }
    }
    val x181 = x2303.slice(0, x3912, x180)
    val x182 = x3910.size
    val x183 = x182./(2)
    var x184: Int = x183
    val x185 = x3910.size
    val x186 = x185.%(2)
    val x187 = x186.==(0)
    val x191 = if(x187) 
    {
      val x188 = x184
      val x189 = x188.-(1)
      val x190 = x184 = x189
      x190
    }
    else
    {
      ()
    }
    
    val x198 = { (x192: SEntry21_IIISSSSSSSSSTSDDDDIIS, x193: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
        val x3966 = x192._4
        val x3967 = x193._4
        val x196 = x3966.compareToIgnoreCase(x3967)
        val x197 = x196.<(0)
        x197
      }
    }
    val x199 = x3910.sortWith(x198)
    val x200 = x184
    val x201 = x199.apply(x200)
    val x202 = x3907 = x201
    x202
  }
  else
  {
    val x3930 = SEntry21_IIISSSSSSSSSTSDDDDIIS(x171, x169, x168, "", "", "", "", "", "", "", "", "", null, "", -100.0, -100.0, -100.0, -100.0, -100, -100, "")
    val x205 = x2303.get(0, x3930)
    val x206 = x3907 = x205
    x206
  }
  
  val x208 = x3907
  val x3935 = x208._3
  val x212 = { x210: SEntry8_IIIITIIB => {
      val x3982 = x210._1
      x3982
    }
  }
  val x213 = Aggregator.max(x212)
  val x3939 = SEntry8_IIIITIIB(-100, x169, x168, x3935, null, -100, -100, false)
  val x216 = x1877.slice(0, x3939, x213)
  val x217 = x213.result
  var x218: Int = 0
  1
}
}
class PaymentTx(x1517: Store[SEntry3_III], x1611: Store[SEntry8_IIIIITDS], x1713: Store[SEntry9_ISSSSSSDD], x1783: Store[SEntry5_IISDS], x1877: Store[SEntry8_IIIITIIB], x1995: Store[SEntry11_IISSSSSSDDI], x2105: Store[SEntry10_IIIIIITIDS], x2303: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x2469: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int) {
def apply(x219: Boolean, x220: Date, x221: Int, x222: Int, x223: Int, x224: Int, x225: Int, x226: Int, x227: Int, x228: String, x229: Double) = {
  val x4035 = SEntry9_ISSSSSSDD(x222, "", "", "", "", "", "", -100.0, -100.0)
  val x232 = x1713.get(0, x4035)
  val x4038 = x232._9
  val x4039 = x4038.+(x229)
  val x4040 = x232._9_=(x4039)
  val x234 = x1713.update(x232)
  val x4042 = SEntry11_IISSSSSSDDI(x223, x222, "", "", "", "", "", "", -100.0, -100.0, -100)
  val x237 = x1995.get(0, x4042)
  val x4045 = x237._10
  val x4046 = x4045.+(x229)
  val x4047 = x237._10_=(x4046)
  val x239 = x1995.update(x237)
  var x4049: SEntry21_IIISSSSSSSSSTSDDDDIIS = null
  val x241 = x224.>(0)
  val x274 = if(x241) 
  {
    val x4052 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
    val x4054 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-100, x226, x225, "", "", x228, "", "", "", "", "", "", null, "", -100.0, -100.0, -100.0, -100.0, -100, -100, "")
    val x247 = { x245: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
        val x246 = x4052.append(x245)
        x246
      }
    }
    val x248 = x2303.slice(0, x4054, x247)
    val x249 = x4052.size
    val x250 = x249./(2)
    var x251: Int = x250
    val x252 = x4052.size
    val x253 = x252.%(2)
    val x254 = x253.==(0)
    val x258 = if(x254) 
    {
      val x255 = x251
      val x256 = x255.-(1)
      val x257 = x251 = x256
      x257
    }
    else
    {
      ()
    }
    
    val x265 = { (x259: SEntry21_IIISSSSSSSSSTSDDDDIIS, x260: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
        val x4163 = x259._4
        val x4164 = x260._4
        val x263 = x4163.compareToIgnoreCase(x4164)
        val x264 = x263.<(0)
        x264
      }
    }
    val x266 = x4052.sortWith(x265)
    val x267 = x251
    val x268 = x266.apply(x267)
    val x269 = x4049 = x268
    x269
  }
  else
  {
    val x4072 = SEntry21_IIISSSSSSSSSTSDDDDIIS(x227, x226, x225, "", "", "", "", "", "", "", "", "", null, "", -100.0, -100.0, -100.0, -100.0, -100, -100, "")
    val x272 = x2303.get(0, x4072)
    val x273 = x4049 = x272
    x273
  }
  
  val x275 = x4049
  val x4077 = x275._21
  var x277: String = x4077
  val x278 = x4049
  val x4080 = x278._14
  val x280 = x4080.contains("BC")
  val x301 = if(x280) 
  {
    val x281 = x4049
    val x4084 = x281._1
    val x283 = x277
    val x285 = "%d %d %d %d %d $%f %s | %s".format(x4084,x226,x225,x223,x222,x229,x220,x283)
    val x286 = x277 = x285
    val x287 = x277
    val x288 = x287.length
    val x289 = x288.>(500)
    val x293 = if(x289) 
    {
      val x290 = x277
      val x291 = x290.substring(0, 500)
      val x292 = x277 = x291
      x292
    }
    else
    {
      ()
    }
    
    val x294 = x4049
    val x4097 = x294._17
    val x4098 = x4097.+(x229)
    val x4099 = x294._17_=(x4098)
    val x296 = x4049
    val x297 = x277
    val x4102 = x296._21_=(x297)
    ()
  }
  else
  {
    val x299 = x4049
    val x4104 = x299._17
    val x4105 = x4104.+(x229)
    val x4106 = x299._17_=(x4105)
    x4106
  }
  
  val x302 = x4049
  val x303 = x2303.update(x302)
  val x4109 = x232._2
  val x4110 = x237._3
  val x306 = x4109.length
  val x307 = x306.>(10)
  val x309 = if(x307) 
  {
    val x308 = x4109.substring(0, 10)
    x308
  }
  else
  {
    x4109
  }
  
  val x310 = x309.+("    ")
  val x311 = x4110.length
  val x312 = x311.>(10)
  val x314 = if(x312) 
  {
    val x313 = x4110.substring(0, 10)
    x313
  }
  else
  {
    x4110
  }
  
  val x315 = x310.+(x314)
  val x316 = x4049
  val x4122 = x316._1
  val x4124 = SEntry8_IIIIITDS(x4122, x226, x225, x223, x222, x220, x229, x315)
  val x320 = x1611.insert(x4124)
  1
}
}
class NewOrderTx(x1517: Store[SEntry3_III], x1611: Store[SEntry8_IIIIITDS], x1713: Store[SEntry9_ISSSSSSDD], x1783: Store[SEntry5_IISDS], x1877: Store[SEntry8_IIIITIIB], x1995: Store[SEntry11_IISSSSSSDDI], x2105: Store[SEntry10_IIIIIITIDS], x2303: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x2469: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int) {
def apply(x321: Boolean, x322: Date, x323: Int, x324: Int, x325: Int, x326: Int, x327: Int, x328: Int, x329: Array[Int], x330: Array[Int], x331: Array[Int], x332: Array[Double], x333: Array[String], x334: Array[Int], x335: Array[String], x336: Array[Double]) = {
  val x340 = if(x321) 
  {
    val x338 = "Started NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(x324,x325,x326)
    val x339 = println(x338)
    x339
  }
  else
  {
    ()
  }
  
  var x341: Int = 0
  var x342: Boolean = false
  val x343 = new Array[String](x327)
  var x344: Boolean = true
  val x369 = while({
    val x345 = x341
    val x346 = x345.<(x327)
    val x348 = x346.&&({
      val x347 = x344
      x347
    })
    x348
  })
  {
    val x349 = x341
    val x350 = x329.apply(x349)
    val x4339 = SEntry5_IISDS(x350, -100, "", -100.0, "")
    val x353 = x1783.get(0, x4339)
    val x354 = x353.==(null)
    val x365 = if(x354) 
    {
      val x355 = x344 = false
      ()
    }
    else
    {
      val x356 = x341
      val x4346 = x353._3
      val x358 = x333.update(x356, x4346)
      val x359 = x341
      val x4349 = x353._4
      val x361 = x332.update(x359, x4349)
      val x362 = x341
      val x4352 = x353._5
      val x364 = x343.update(x362, x4352)
      x364
    }
    
    val x366 = x341
    val x367 = x366.+(1)
    val x368 = x341 = x367
    ()
  }
  val x370 = x344
  val x479 = if(x370) 
  {
    val x4359 = SEntry21_IIISSSSSSSSSTSDDDDIIS(x326, x325, x324, "", "", "", "", "", "", "", "", "", null, "", -100.0, -100.0, -100.0, -100.0, -100, -100, "")
    val x373 = x2303.get(0, x4359)
    val x4362 = SEntry9_ISSSSSSDD(x324, "", "", "", "", "", "", -100.0, -100.0)
    val x376 = x1713.get(0, x4362)
    val x4365 = SEntry11_IISSSSSSDDI(x325, x324, "", "", "", "", "", "", -100.0, -100.0, -100)
    val x379 = x1995.get(0, x4365)
    val x4368 = x379._11
    val x4369 = x379._11
    val x4370 = x4369.+(1)
    val x4371 = x379._11_=(x4370)
    val x382 = x1995.update(x379)
    val x383 = x328.>(0)
    val x4375 = SEntry8_IIIITIIB(x4368, x325, x324, x326, x322, -1, x327, x383)
    val x386 = x1877.insert(x4375)
    val x4378 = SEntry3_III(x4368, x325, x324)
    val x389 = x1517.insert(x4378)
    var x390: Double = 0.0
    val x391 = x341 = 0
    val x478 = while({
      val x392 = x341
      val x393 = x392.<(x327)
      x393
    })
    {
      val x394 = x341
      val x395 = x330.apply(x394)
      val x396 = x341
      val x397 = x329.apply(x396)
      val x398 = x341
      val x399 = x331.apply(x398)
      val x4391 = SEntry17_IIISSSSSSSSSSIIIS(x397, x395, -100, "", "", "", "", "", "", "", "", "", "", -100, -100, -100, "")
      val x401 = x2469.get(0, x4391)
      val x402 = x325.==(1)
      val x429 = if(x402) 
      {
        val x4395 = x401._4
        x4395
      }
      else
      {
        val x404 = x325.==(2)
        val x428 = if(x404) 
        {
          val x4398 = x401._5
          x4398
        }
        else
        {
          val x406 = x325.==(3)
          val x427 = if(x406) 
          {
            val x4401 = x401._6
            x4401
          }
          else
          {
            val x408 = x325.==(4)
            val x426 = if(x408) 
            {
              val x4404 = x401._7
              x4404
            }
            else
            {
              val x410 = x325.==(5)
              val x425 = if(x410) 
              {
                val x4407 = x401._8
                x4407
              }
              else
              {
                val x412 = x325.==(6)
                val x424 = if(x412) 
                {
                  val x4410 = x401._9
                  x4410
                }
                else
                {
                  val x414 = x325.==(7)
                  val x423 = if(x414) 
                  {
                    val x4413 = x401._10
                    x4413
                  }
                  else
                  {
                    val x416 = x325.==(8)
                    val x422 = if(x416) 
                    {
                      val x4416 = x401._11
                      x4416
                    }
                    else
                    {
                      val x418 = x325.==(9)
                      val x421 = if(x418) 
                      {
                        val x4419 = x401._12
                        x4419
                      }
                      else
                      {
                        val x4420 = x401._13
                        x4420
                      }
                      
                      x421
                    }
                    
                    x422
                  }
                  
                  x423
                }
                
                x424
              }
              
              x425
            }
            
            x426
          }
          
          x427
        }
        
        x428
      }
      
      val x4421 = x401._3
      val x431 = x341
      val x432 = x334.update(x431, x4421)
      val x4424 = x373._14
      val x434 = x4424.contains("original")
      val x437 = x434.&&({
        val x4427 = x401._17
        val x436 = x4427.contains("original")
        x436
      })
      val x442 = if(x437) 
      {
        val x438 = x341
        val x439 = x335.update(x438, "B")
        ()
      }
      else
      {
        val x440 = x341
        val x441 = x335.update(x440, "G")
        ()
      }
      
      val x443 = x4421.-(x399)
      val x4435 = x401._3_=(x443)
      val x445 = x4421.<=(x399)
      val x447 = if(x445) 
      {
        val x4438 = x401._3
        val x4439 = x4438.+(91)
        val x4440 = x401._3_=(x4439)
        x4440
      }
      else
      {
        ()
      }
      
      var x448: Int = 0
      val x449 = x395.!=(x324)
      val x451 = if(x449) 
      {
        val x450 = x448 = 1
        x450
      }
      else
      {
        ()
      }
      
      val x452 = x2469.update(x401)
      val x4446 = x373._16
      val x4447 = x376._8
      val x4448 = x379._9
      val x456 = x341
      val x457 = x332.apply(x456)
      val x458 = x399.toDouble
      val x459 = x458.*(x457)
      val x460 = 1.0.+(x4447)
      val x461 = x460.+(x4448)
      val x462 = x459.*(x461)
      val x463 = 1.0.-(x4446)
      val x464 = x462.*(x463)
      val x465 = x341
      val x466 = x336.update(x465, x464)
      val x467 = x390
      val x468 = x467.+(x464)
      val x469 = x390 = x468
      val x470 = x341
      val x471 = x470.+(1)
      val x4466 = SEntry10_IIIIIITIDS(x4368, x325, x324, x471, x397, x395, null, x399, x464, x429)
      val x474 = x2105.insert(x4466)
      val x475 = x341
      val x476 = x475.+(1)
      val x477 = x341 = x476
      ()
    }
    ()
  }
  else
  {
    ()
  }
  
  1
}
}
