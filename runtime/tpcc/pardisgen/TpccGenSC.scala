
package tpcc.sc
import ddbt.lib.store._
import scala.collection.mutable.{ArrayBuffer,Set}
import java.util.Date
 class SCExecutor 
{
  val x914 = { x18: SEntry3_III => {
      val x4103 = x18._1
      x4103
    }
  }
   object SEntry3_III_Idx0 extends EntryIdx[SEntry3_III] {
    override def hash(x2401 : SEntry3_III) = {
      var x2402: Int = -889275714
      val x2403 = x2401._2
      val x2404 = x2403.hashCode()
      val x2405 = -862048943.*(x2404)
      val x2406 = x2405.<<(15)
      val x2407 = x2405.>>>(-15)
      val x2408 = x2406.|(x2407)
      val x2409 = x2408.*(461845907)
      val x2410 = x2402
      val x2411 = x2409.^(x2410)
      val x2412 = x2411.<<(13)
      val x2413 = x2411.>>>(-13)
      val x2414 = x2412.|(x2413)
      val x2415 = x2414.*(5)
      val x2416 = x2415.+(-430675100)
      x2402 = x2416
      val x2418 = x2401._3
      val x2419 = x2418.hashCode()
      val x2420 = -862048943.*(x2419)
      val x2421 = x2420.<<(15)
      val x2422 = x2420.>>>(-15)
      val x2423 = x2421.|(x2422)
      val x2424 = x2423.*(461845907)
      val x2425 = x2402
      val x2426 = x2424.^(x2425)
      val x2427 = x2426.<<(13)
      val x2428 = x2426.>>>(-13)
      val x2429 = x2427.|(x2428)
      val x2430 = x2429.*(5)
      val x2431 = x2430.+(-430675100)
      x2402 = x2431
      val x2433 = x2402
      val x2434 = x2433.^(2)
      val x2435 = x2434.>>>(16)
      val x2436 = x2434.^(x2435)
      val x2437 = x2436.*(-2048144789)
      val x2438 = x2437.>>>(13)
      val x2439 = x2437.^(x2438)
      val x2440 = x2439.*(-1028477387)
      val x2441 = x2440.>>>(16)
      val x2442 = x2440.^(x2441)
      x2442
    }
    override def cmp(x2444 : SEntry3_III , x2445 : SEntry3_III) = {
      val x2446 = x914.apply(x2444)
      val x2447 = x914.apply(x2445)
      val x2448 = x2446.==(x2447)
      val x2451 = if(x2448) 
      {
        0
      }
      else
      {
        val x2449 = x2446.>(x2447)
        val x2450 = if(x2449) 
        {
          1
        }
        else
        {
          -1
        }
        
        x2450
      }
      
      x2451
    }
  }
   object SEntry3_III_Idx1 extends EntryIdx[SEntry3_III] {
    override def hash(x2454 : SEntry3_III) = {
      var x2455: Int = -889275714
      val x2456 = x2454._2
      val x2457 = x2456.hashCode()
      val x2458 = -862048943.*(x2457)
      val x2459 = x2458.<<(15)
      val x2460 = x2458.>>>(-15)
      val x2461 = x2459.|(x2460)
      val x2462 = x2461.*(461845907)
      val x2463 = x2455
      val x2464 = x2462.^(x2463)
      val x2465 = x2464.<<(13)
      val x2466 = x2464.>>>(-13)
      val x2467 = x2465.|(x2466)
      val x2468 = x2467.*(5)
      val x2469 = x2468.+(-430675100)
      x2455 = x2469
      val x2471 = x2454._3
      val x2472 = x2471.hashCode()
      val x2473 = -862048943.*(x2472)
      val x2474 = x2473.<<(15)
      val x2475 = x2473.>>>(-15)
      val x2476 = x2474.|(x2475)
      val x2477 = x2476.*(461845907)
      val x2478 = x2455
      val x2479 = x2477.^(x2478)
      val x2480 = x2479.<<(13)
      val x2481 = x2479.>>>(-13)
      val x2482 = x2480.|(x2481)
      val x2483 = x2482.*(5)
      val x2484 = x2483.+(-430675100)
      x2455 = x2484
      val x2486 = x2455
      val x2487 = x2486.^(2)
      val x2488 = x2487.>>>(16)
      val x2489 = x2487.^(x2488)
      val x2490 = x2489.*(-2048144789)
      val x2491 = x2490.>>>(13)
      val x2492 = x2490.^(x2491)
      val x2493 = x2492.*(-1028477387)
      val x2494 = x2493.>>>(16)
      val x2495 = x2493.^(x2494)
      x2495
    }
    override def cmp(x2497 : SEntry3_III , x2498 : SEntry3_III) = {
      val x2499 = x2497._2
      val x2500 = x2498._2
      val x2501 = x2499.==(x2500)
      val x2505 = x2501.&&({
        val x2502 = x2497._3
        val x2503 = x2498._3
        val x2504 = x2502.==(x2503)
        x2504
      })
      val x2506 = if(x2505) 
      {
        0
      }
      else
      {
        1
      }
      
      x2506
    }
  }
  val x2510 = Array[EntryIdx[SEntry3_III]](SEntry3_III_Idx0, SEntry3_III_Idx1)
  val x2511 = new Store[SEntry3_III](2, x2510)
  x2511.index(0, ISliceHeapMin, false, 1)
  x2511.index(1, INone, false, -1)
   object SEntry8_IIIIITDS_Idx2 extends EntryIdx[SEntry8_IIIIITDS] {
    override def hash(x2515 : SEntry8_IIIIITDS) = {
      var x2516: Int = -889275714
      val x2517 = x2516
      val x2518 = x2517.^(2)
      val x2519 = x2518.>>>(16)
      val x2520 = x2518.^(x2519)
      val x2521 = x2520.*(-2048144789)
      val x2522 = x2521.>>>(13)
      val x2523 = x2521.^(x2522)
      val x2524 = x2523.*(-1028477387)
      val x2525 = x2524.>>>(16)
      val x2526 = x2524.^(x2525)
      x2526
    }
    override def cmp(x2528 : SEntry8_IIIIITDS , x2529 : SEntry8_IIIIITDS) = {
      val x2530 = x2528._1
      val x2531 = x2529._1
      val x2532 = x2530.==(-1)
      val x2534 = x2532.||({
        val x2533 = x2531.==(-1)
        x2533
      })
      val x2536 = x2534.||({
        val x2535 = x2530.==(x2531)
        x2535
      })
      val x2544 = x2536.&&({
        val x2537 = x2528._2
        val x2538 = x2529._2
        val x2539 = x2537.==(-1)
        val x2541 = x2539.||({
          val x2540 = x2538.==(-1)
          x2540
        })
        val x2543 = x2541.||({
          val x2542 = x2537.==(x2538)
          x2542
        })
        x2543
      })
      val x2552 = x2544.&&({
        val x2545 = x2528._3
        val x2546 = x2529._3
        val x2547 = x2545.==(-1)
        val x2549 = x2547.||({
          val x2548 = x2546.==(-1)
          x2548
        })
        val x2551 = x2549.||({
          val x2550 = x2545.==(x2546)
          x2550
        })
        x2551
      })
      val x2560 = x2552.&&({
        val x2553 = x2528._4
        val x2554 = x2529._4
        val x2555 = x2553.==(-1)
        val x2557 = x2555.||({
          val x2556 = x2554.==(-1)
          x2556
        })
        val x2559 = x2557.||({
          val x2558 = x2553.==(x2554)
          x2558
        })
        x2559
      })
      val x2568 = x2560.&&({
        val x2561 = x2528._5
        val x2562 = x2529._5
        val x2563 = x2561.==(-1)
        val x2565 = x2563.||({
          val x2564 = x2562.==(-1)
          x2564
        })
        val x2567 = x2565.||({
          val x2566 = x2561.==(x2562)
          x2566
        })
        x2567
      })
      val x2576 = x2568.&&({
        val x2569 = x2528._6
        val x2570 = x2529._6
        val x2571 = x2569.==(null)
        val x2573 = x2571.||({
          val x2572 = x2570.==(null)
          x2572
        })
        val x2575 = x2573.||({
          val x2574 = x2569.==(x2570)
          x2574
        })
        x2575
      })
      val x2584 = x2576.&&({
        val x2577 = x2528._7
        val x2578 = x2529._7
        val x2579 = x2577.==(-1.0)
        val x2581 = x2579.||({
          val x2580 = x2578.==(-1.0)
          x2580
        })
        val x2583 = x2581.||({
          val x2582 = x2577.==(x2578)
          x2582
        })
        x2583
      })
      val x2585 = if(x2584) 
      {
        0
      }
      else
      {
        1
      }
      
      x2585
    }
  }
  val x2589 = Array[EntryIdx[SEntry8_IIIIITDS]](SEntry8_IIIIITDS_Idx2)
  val x2590 = new Store[SEntry8_IIIIITDS](1, x2589)
  x2590.index(0, IList, false, -1)
   object SEntry9_ISSSSSSDD_Idx3 extends EntryIdx[SEntry9_ISSSSSSDD] {
    override def hash(x2593 : SEntry9_ISSSSSSDD) = {
      var x2594: Int = -889275714
      val x2595 = x2593._1
      val x2596 = x2595.hashCode()
      val x2597 = -862048943.*(x2596)
      val x2598 = x2597.<<(15)
      val x2599 = x2597.>>>(-15)
      val x2600 = x2598.|(x2599)
      val x2601 = x2600.*(461845907)
      val x2602 = x2594
      val x2603 = x2601.^(x2602)
      val x2604 = x2603.<<(13)
      val x2605 = x2603.>>>(-13)
      val x2606 = x2604.|(x2605)
      val x2607 = x2606.*(5)
      val x2608 = x2607.+(-430675100)
      x2594 = x2608
      val x2610 = x2594
      val x2611 = x2610.^(2)
      val x2612 = x2611.>>>(16)
      val x2613 = x2611.^(x2612)
      val x2614 = x2613.*(-2048144789)
      val x2615 = x2614.>>>(13)
      val x2616 = x2614.^(x2615)
      val x2617 = x2616.*(-1028477387)
      val x2618 = x2617.>>>(16)
      val x2619 = x2617.^(x2618)
      x2619
    }
    override def cmp(x2621 : SEntry9_ISSSSSSDD , x2622 : SEntry9_ISSSSSSDD) = {
      val x2623 = x2621._1
      val x2624 = x2622._1
      val x2625 = x2623.==(x2624)
      val x2626 = if(x2625) 
      {
        0
      }
      else
      {
        1
      }
      
      x2626
    }
  }
  val x2630 = Array[EntryIdx[SEntry9_ISSSSSSDD]](SEntry9_ISSSSSSDD_Idx3)
  val x2631 = new Store[SEntry9_ISSSSSSDD](1, x2630)
  x2631.index(0, IHash, true, -1)
   object SEntry5_IISDS_Idx4 extends EntryIdx[SEntry5_IISDS] {
    override def hash(x2633 : SEntry5_IISDS) = {
      var x2634: Int = -889275714
      val x2635 = x2633._1
      val x2636 = x2635.hashCode()
      val x2637 = -862048943.*(x2636)
      val x2638 = x2637.<<(15)
      val x2639 = x2637.>>>(-15)
      val x2640 = x2638.|(x2639)
      val x2641 = x2640.*(461845907)
      val x2642 = x2634
      val x2643 = x2641.^(x2642)
      val x2644 = x2643.<<(13)
      val x2645 = x2643.>>>(-13)
      val x2646 = x2644.|(x2645)
      val x2647 = x2646.*(5)
      val x2648 = x2647.+(-430675100)
      x2634 = x2648
      val x2650 = x2634
      val x2651 = x2650.^(2)
      val x2652 = x2651.>>>(16)
      val x2653 = x2651.^(x2652)
      val x2654 = x2653.*(-2048144789)
      val x2655 = x2654.>>>(13)
      val x2656 = x2654.^(x2655)
      val x2657 = x2656.*(-1028477387)
      val x2658 = x2657.>>>(16)
      val x2659 = x2657.^(x2658)
      x2659
    }
    override def cmp(x2661 : SEntry5_IISDS , x2662 : SEntry5_IISDS) = {
      val x2663 = x2661._1
      val x2664 = x2662._1
      val x2665 = x2663.==(x2664)
      val x2666 = if(x2665) 
      {
        0
      }
      else
      {
        1
      }
      
      x2666
    }
  }
  val x2670 = Array[EntryIdx[SEntry5_IISDS]](SEntry5_IISDS_Idx4)
  val x2671 = new Store[SEntry5_IISDS](1, x2670)
  x2671.index(0, IHash, true, -1)
  val x936 = { x210: SEntry8_IIIITIIB => {
      val x4379 = x210._1
      x4379
    }
  }
   object SEntry8_IIIITIIB_Idx5 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x2677 : SEntry8_IIIITIIB) = {
      var x2678: Int = -889275714
      val x2679 = x2677._1
      val x2680 = x2679.hashCode()
      val x2681 = -862048943.*(x2680)
      val x2682 = x2681.<<(15)
      val x2683 = x2681.>>>(-15)
      val x2684 = x2682.|(x2683)
      val x2685 = x2684.*(461845907)
      val x2686 = x2678
      val x2687 = x2685.^(x2686)
      val x2688 = x2687.<<(13)
      val x2689 = x2687.>>>(-13)
      val x2690 = x2688.|(x2689)
      val x2691 = x2690.*(5)
      val x2692 = x2691.+(-430675100)
      x2678 = x2692
      val x2694 = x2677._2
      val x2695 = x2694.hashCode()
      val x2696 = -862048943.*(x2695)
      val x2697 = x2696.<<(15)
      val x2698 = x2696.>>>(-15)
      val x2699 = x2697.|(x2698)
      val x2700 = x2699.*(461845907)
      val x2701 = x2678
      val x2702 = x2700.^(x2701)
      val x2703 = x2702.<<(13)
      val x2704 = x2702.>>>(-13)
      val x2705 = x2703.|(x2704)
      val x2706 = x2705.*(5)
      val x2707 = x2706.+(-430675100)
      x2678 = x2707
      val x2709 = x2677._3
      val x2710 = x2709.hashCode()
      val x2711 = -862048943.*(x2710)
      val x2712 = x2711.<<(15)
      val x2713 = x2711.>>>(-15)
      val x2714 = x2712.|(x2713)
      val x2715 = x2714.*(461845907)
      val x2716 = x2678
      val x2717 = x2715.^(x2716)
      val x2718 = x2717.<<(13)
      val x2719 = x2717.>>>(-13)
      val x2720 = x2718.|(x2719)
      val x2721 = x2720.*(5)
      val x2722 = x2721.+(-430675100)
      x2678 = x2722
      val x2724 = x2678
      val x2725 = x2724.^(2)
      val x2726 = x2725.>>>(16)
      val x2727 = x2725.^(x2726)
      val x2728 = x2727.*(-2048144789)
      val x2729 = x2728.>>>(13)
      val x2730 = x2728.^(x2729)
      val x2731 = x2730.*(-1028477387)
      val x2732 = x2731.>>>(16)
      val x2733 = x2731.^(x2732)
      x2733
    }
    override def cmp(x2735 : SEntry8_IIIITIIB , x2736 : SEntry8_IIIITIIB) = {
      val x2737 = x2735._1
      val x2738 = x2736._1
      val x2739 = x2737.==(x2738)
      val x2743 = x2739.&&({
        val x2740 = x2735._2
        val x2741 = x2736._2
        val x2742 = x2740.==(x2741)
        x2742
      })
      val x2747 = x2743.&&({
        val x2744 = x2735._3
        val x2745 = x2736._3
        val x2746 = x2744.==(x2745)
        x2746
      })
      val x2748 = if(x2747) 
      {
        0
      }
      else
      {
        1
      }
      
      x2748
    }
  }
   object SEntry8_IIIITIIB_Idx6 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x2751 : SEntry8_IIIITIIB) = {
      var x2752: Int = -889275714
      val x2753 = x2751._2
      val x2754 = x2753.hashCode()
      val x2755 = -862048943.*(x2754)
      val x2756 = x2755.<<(15)
      val x2757 = x2755.>>>(-15)
      val x2758 = x2756.|(x2757)
      val x2759 = x2758.*(461845907)
      val x2760 = x2752
      val x2761 = x2759.^(x2760)
      val x2762 = x2761.<<(13)
      val x2763 = x2761.>>>(-13)
      val x2764 = x2762.|(x2763)
      val x2765 = x2764.*(5)
      val x2766 = x2765.+(-430675100)
      x2752 = x2766
      val x2768 = x2751._3
      val x2769 = x2768.hashCode()
      val x2770 = -862048943.*(x2769)
      val x2771 = x2770.<<(15)
      val x2772 = x2770.>>>(-15)
      val x2773 = x2771.|(x2772)
      val x2774 = x2773.*(461845907)
      val x2775 = x2752
      val x2776 = x2774.^(x2775)
      val x2777 = x2776.<<(13)
      val x2778 = x2776.>>>(-13)
      val x2779 = x2777.|(x2778)
      val x2780 = x2779.*(5)
      val x2781 = x2780.+(-430675100)
      x2752 = x2781
      val x2783 = x2751._4
      val x2784 = x2783.hashCode()
      val x2785 = -862048943.*(x2784)
      val x2786 = x2785.<<(15)
      val x2787 = x2785.>>>(-15)
      val x2788 = x2786.|(x2787)
      val x2789 = x2788.*(461845907)
      val x2790 = x2752
      val x2791 = x2789.^(x2790)
      val x2792 = x2791.<<(13)
      val x2793 = x2791.>>>(-13)
      val x2794 = x2792.|(x2793)
      val x2795 = x2794.*(5)
      val x2796 = x2795.+(-430675100)
      x2752 = x2796
      val x2798 = x2752
      val x2799 = x2798.^(2)
      val x2800 = x2799.>>>(16)
      val x2801 = x2799.^(x2800)
      val x2802 = x2801.*(-2048144789)
      val x2803 = x2802.>>>(13)
      val x2804 = x2802.^(x2803)
      val x2805 = x2804.*(-1028477387)
      val x2806 = x2805.>>>(16)
      val x2807 = x2805.^(x2806)
      x2807
    }
    override def cmp(x2809 : SEntry8_IIIITIIB , x2810 : SEntry8_IIIITIIB) = {
      val x2811 = x936.apply(x2809)
      val x2812 = x936.apply(x2810)
      val x2813 = x2811.==(x2812)
      val x2816 = if(x2813) 
      {
        0
      }
      else
      {
        val x2814 = x2811.>(x2812)
        val x2815 = if(x2814) 
        {
          1
        }
        else
        {
          -1
        }
        
        x2815
      }
      
      x2816
    }
  }
   object SEntry8_IIIITIIB_Idx7 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x2819 : SEntry8_IIIITIIB) = {
      var x2820: Int = -889275714
      val x2821 = x2819._2
      val x2822 = x2821.hashCode()
      val x2823 = -862048943.*(x2822)
      val x2824 = x2823.<<(15)
      val x2825 = x2823.>>>(-15)
      val x2826 = x2824.|(x2825)
      val x2827 = x2826.*(461845907)
      val x2828 = x2820
      val x2829 = x2827.^(x2828)
      val x2830 = x2829.<<(13)
      val x2831 = x2829.>>>(-13)
      val x2832 = x2830.|(x2831)
      val x2833 = x2832.*(5)
      val x2834 = x2833.+(-430675100)
      x2820 = x2834
      val x2836 = x2819._3
      val x2837 = x2836.hashCode()
      val x2838 = -862048943.*(x2837)
      val x2839 = x2838.<<(15)
      val x2840 = x2838.>>>(-15)
      val x2841 = x2839.|(x2840)
      val x2842 = x2841.*(461845907)
      val x2843 = x2820
      val x2844 = x2842.^(x2843)
      val x2845 = x2844.<<(13)
      val x2846 = x2844.>>>(-13)
      val x2847 = x2845.|(x2846)
      val x2848 = x2847.*(5)
      val x2849 = x2848.+(-430675100)
      x2820 = x2849
      val x2851 = x2819._4
      val x2852 = x2851.hashCode()
      val x2853 = -862048943.*(x2852)
      val x2854 = x2853.<<(15)
      val x2855 = x2853.>>>(-15)
      val x2856 = x2854.|(x2855)
      val x2857 = x2856.*(461845907)
      val x2858 = x2820
      val x2859 = x2857.^(x2858)
      val x2860 = x2859.<<(13)
      val x2861 = x2859.>>>(-13)
      val x2862 = x2860.|(x2861)
      val x2863 = x2862.*(5)
      val x2864 = x2863.+(-430675100)
      x2820 = x2864
      val x2866 = x2820
      val x2867 = x2866.^(2)
      val x2868 = x2867.>>>(16)
      val x2869 = x2867.^(x2868)
      val x2870 = x2869.*(-2048144789)
      val x2871 = x2870.>>>(13)
      val x2872 = x2870.^(x2871)
      val x2873 = x2872.*(-1028477387)
      val x2874 = x2873.>>>(16)
      val x2875 = x2873.^(x2874)
      x2875
    }
    override def cmp(x2877 : SEntry8_IIIITIIB , x2878 : SEntry8_IIIITIIB) = {
      val x2879 = x2877._2
      val x2880 = x2878._2
      val x2881 = x2879.==(x2880)
      val x2885 = x2881.&&({
        val x2882 = x2877._3
        val x2883 = x2878._3
        val x2884 = x2882.==(x2883)
        x2884
      })
      val x2889 = x2885.&&({
        val x2886 = x2877._4
        val x2887 = x2878._4
        val x2888 = x2886.==(x2887)
        x2888
      })
      val x2890 = if(x2889) 
      {
        0
      }
      else
      {
        1
      }
      
      x2890
    }
  }
  val x2894 = Array[EntryIdx[SEntry8_IIIITIIB]](SEntry8_IIIITIIB_Idx5, SEntry8_IIIITIIB_Idx6, SEntry8_IIIITIIB_Idx7)
  val x2895 = new Store[SEntry8_IIIITIIB](3, x2894)
  x2895.index(0, IHash, true, -1)
  x2895.index(1, ISliceHeapMax, false, 2)
  x2895.index(2, INone, false, -1)
   object SEntry11_IISSSSSSDDI_Idx8 extends EntryIdx[SEntry11_IISSSSSSDDI] {
    override def hash(x2900 : SEntry11_IISSSSSSDDI) = {
      var x2901: Int = -889275714
      val x2902 = x2900._1
      val x2903 = x2902.hashCode()
      val x2904 = -862048943.*(x2903)
      val x2905 = x2904.<<(15)
      val x2906 = x2904.>>>(-15)
      val x2907 = x2905.|(x2906)
      val x2908 = x2907.*(461845907)
      val x2909 = x2901
      val x2910 = x2908.^(x2909)
      val x2911 = x2910.<<(13)
      val x2912 = x2910.>>>(-13)
      val x2913 = x2911.|(x2912)
      val x2914 = x2913.*(5)
      val x2915 = x2914.+(-430675100)
      x2901 = x2915
      val x2917 = x2900._2
      val x2918 = x2917.hashCode()
      val x2919 = -862048943.*(x2918)
      val x2920 = x2919.<<(15)
      val x2921 = x2919.>>>(-15)
      val x2922 = x2920.|(x2921)
      val x2923 = x2922.*(461845907)
      val x2924 = x2901
      val x2925 = x2923.^(x2924)
      val x2926 = x2925.<<(13)
      val x2927 = x2925.>>>(-13)
      val x2928 = x2926.|(x2927)
      val x2929 = x2928.*(5)
      val x2930 = x2929.+(-430675100)
      x2901 = x2930
      val x2932 = x2901
      val x2933 = x2932.^(2)
      val x2934 = x2933.>>>(16)
      val x2935 = x2933.^(x2934)
      val x2936 = x2935.*(-2048144789)
      val x2937 = x2936.>>>(13)
      val x2938 = x2936.^(x2937)
      val x2939 = x2938.*(-1028477387)
      val x2940 = x2939.>>>(16)
      val x2941 = x2939.^(x2940)
      x2941
    }
    override def cmp(x2943 : SEntry11_IISSSSSSDDI , x2944 : SEntry11_IISSSSSSDDI) = {
      val x2945 = x2943._1
      val x2946 = x2944._1
      val x2947 = x2945.==(x2946)
      val x2951 = x2947.&&({
        val x2948 = x2943._2
        val x2949 = x2944._2
        val x2950 = x2948.==(x2949)
        x2950
      })
      val x2952 = if(x2951) 
      {
        0
      }
      else
      {
        1
      }
      
      x2952
    }
  }
  val x2956 = Array[EntryIdx[SEntry11_IISSSSSSDDI]](SEntry11_IISSSSSSDDI_Idx8)
  val x2957 = new Store[SEntry11_IISSSSSSDDI](1, x2956)
  x2957.index(0, IHash, true, -1)
   object SEntry10_IIIIIITIDS_Idx9 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x2960 : SEntry10_IIIIIITIDS) = {
      var x2961: Int = -889275714
      val x2962 = x2960._1
      val x2963 = x2962.hashCode()
      val x2964 = -862048943.*(x2963)
      val x2965 = x2964.<<(15)
      val x2966 = x2964.>>>(-15)
      val x2967 = x2965.|(x2966)
      val x2968 = x2967.*(461845907)
      val x2969 = x2961
      val x2970 = x2968.^(x2969)
      val x2971 = x2970.<<(13)
      val x2972 = x2970.>>>(-13)
      val x2973 = x2971.|(x2972)
      val x2974 = x2973.*(5)
      val x2975 = x2974.+(-430675100)
      x2961 = x2975
      val x2977 = x2960._2
      val x2978 = x2977.hashCode()
      val x2979 = -862048943.*(x2978)
      val x2980 = x2979.<<(15)
      val x2981 = x2979.>>>(-15)
      val x2982 = x2980.|(x2981)
      val x2983 = x2982.*(461845907)
      val x2984 = x2961
      val x2985 = x2983.^(x2984)
      val x2986 = x2985.<<(13)
      val x2987 = x2985.>>>(-13)
      val x2988 = x2986.|(x2987)
      val x2989 = x2988.*(5)
      val x2990 = x2989.+(-430675100)
      x2961 = x2990
      val x2992 = x2960._3
      val x2993 = x2992.hashCode()
      val x2994 = -862048943.*(x2993)
      val x2995 = x2994.<<(15)
      val x2996 = x2994.>>>(-15)
      val x2997 = x2995.|(x2996)
      val x2998 = x2997.*(461845907)
      val x2999 = x2961
      val x3000 = x2998.^(x2999)
      val x3001 = x3000.<<(13)
      val x3002 = x3000.>>>(-13)
      val x3003 = x3001.|(x3002)
      val x3004 = x3003.*(5)
      val x3005 = x3004.+(-430675100)
      x2961 = x3005
      val x3007 = x2961
      val x3008 = x3007.^(2)
      val x3009 = x3008.>>>(16)
      val x3010 = x3008.^(x3009)
      val x3011 = x3010.*(-2048144789)
      val x3012 = x3011.>>>(13)
      val x3013 = x3011.^(x3012)
      val x3014 = x3013.*(-1028477387)
      val x3015 = x3014.>>>(16)
      val x3016 = x3014.^(x3015)
      x3016
    }
    override def cmp(x3018 : SEntry10_IIIIIITIDS , x3019 : SEntry10_IIIIIITIDS) = {
      val x3020 = x3018._1
      val x3021 = x3019._1
      val x3022 = x3020.==(x3021)
      val x3026 = x3022.&&({
        val x3023 = x3018._2
        val x3024 = x3019._2
        val x3025 = x3023.==(x3024)
        x3025
      })
      val x3030 = x3026.&&({
        val x3027 = x3018._3
        val x3028 = x3019._3
        val x3029 = x3027.==(x3028)
        x3029
      })
      val x3031 = if(x3030) 
      {
        0
      }
      else
      {
        1
      }
      
      x3031
    }
  }
  val x3035 = Array[EntryIdx[SEntry10_IIIIIITIDS]](SEntry10_IIIIIITIDS_Idx9)
  val x3036 = new Store[SEntry10_IIIIIITIDS](1, x3035)
  x3036.index(0, IHash, false, -1)
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx10 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x3039 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x3040: Int = -889275714
      val x3041 = x3039._1
      val x3042 = x3041.hashCode()
      val x3043 = -862048943.*(x3042)
      val x3044 = x3043.<<(15)
      val x3045 = x3043.>>>(-15)
      val x3046 = x3044.|(x3045)
      val x3047 = x3046.*(461845907)
      val x3048 = x3040
      val x3049 = x3047.^(x3048)
      val x3050 = x3049.<<(13)
      val x3051 = x3049.>>>(-13)
      val x3052 = x3050.|(x3051)
      val x3053 = x3052.*(5)
      val x3054 = x3053.+(-430675100)
      x3040 = x3054
      val x3056 = x3039._2
      val x3057 = x3056.hashCode()
      val x3058 = -862048943.*(x3057)
      val x3059 = x3058.<<(15)
      val x3060 = x3058.>>>(-15)
      val x3061 = x3059.|(x3060)
      val x3062 = x3061.*(461845907)
      val x3063 = x3040
      val x3064 = x3062.^(x3063)
      val x3065 = x3064.<<(13)
      val x3066 = x3064.>>>(-13)
      val x3067 = x3065.|(x3066)
      val x3068 = x3067.*(5)
      val x3069 = x3068.+(-430675100)
      x3040 = x3069
      val x3071 = x3039._3
      val x3072 = x3071.hashCode()
      val x3073 = -862048943.*(x3072)
      val x3074 = x3073.<<(15)
      val x3075 = x3073.>>>(-15)
      val x3076 = x3074.|(x3075)
      val x3077 = x3076.*(461845907)
      val x3078 = x3040
      val x3079 = x3077.^(x3078)
      val x3080 = x3079.<<(13)
      val x3081 = x3079.>>>(-13)
      val x3082 = x3080.|(x3081)
      val x3083 = x3082.*(5)
      val x3084 = x3083.+(-430675100)
      x3040 = x3084
      val x3086 = x3040
      val x3087 = x3086.^(2)
      val x3088 = x3087.>>>(16)
      val x3089 = x3087.^(x3088)
      val x3090 = x3089.*(-2048144789)
      val x3091 = x3090.>>>(13)
      val x3092 = x3090.^(x3091)
      val x3093 = x3092.*(-1028477387)
      val x3094 = x3093.>>>(16)
      val x3095 = x3093.^(x3094)
      x3095
    }
    override def cmp(x3097 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x3098 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      val x3099 = x3097._1
      val x3100 = x3098._1
      val x3101 = x3099.==(x3100)
      val x3105 = x3101.&&({
        val x3102 = x3097._2
        val x3103 = x3098._2
        val x3104 = x3102.==(x3103)
        x3104
      })
      val x3109 = x3105.&&({
        val x3106 = x3097._3
        val x3107 = x3098._3
        val x3108 = x3106.==(x3107)
        x3108
      })
      val x3110 = if(x3109) 
      {
        0
      }
      else
      {
        1
      }
      
      x3110
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx11 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x3113 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x3114: Int = -889275714
      val x3115 = x3113._2
      val x3116 = x3115.hashCode()
      val x3117 = -862048943.*(x3116)
      val x3118 = x3117.<<(15)
      val x3119 = x3117.>>>(-15)
      val x3120 = x3118.|(x3119)
      val x3121 = x3120.*(461845907)
      val x3122 = x3114
      val x3123 = x3121.^(x3122)
      val x3124 = x3123.<<(13)
      val x3125 = x3123.>>>(-13)
      val x3126 = x3124.|(x3125)
      val x3127 = x3126.*(5)
      val x3128 = x3127.+(-430675100)
      x3114 = x3128
      val x3130 = x3113._3
      val x3131 = x3130.hashCode()
      val x3132 = -862048943.*(x3131)
      val x3133 = x3132.<<(15)
      val x3134 = x3132.>>>(-15)
      val x3135 = x3133.|(x3134)
      val x3136 = x3135.*(461845907)
      val x3137 = x3114
      val x3138 = x3136.^(x3137)
      val x3139 = x3138.<<(13)
      val x3140 = x3138.>>>(-13)
      val x3141 = x3139.|(x3140)
      val x3142 = x3141.*(5)
      val x3143 = x3142.+(-430675100)
      x3114 = x3143
      val x3145 = x3113._6
      val x3146 = x3145.hashCode()
      val x3147 = -862048943.*(x3146)
      val x3148 = x3147.<<(15)
      val x3149 = x3147.>>>(-15)
      val x3150 = x3148.|(x3149)
      val x3151 = x3150.*(461845907)
      val x3152 = x3114
      val x3153 = x3151.^(x3152)
      val x3154 = x3153.<<(13)
      val x3155 = x3153.>>>(-13)
      val x3156 = x3154.|(x3155)
      val x3157 = x3156.*(5)
      val x3158 = x3157.+(-430675100)
      x3114 = x3158
      val x3160 = x3114
      val x3161 = x3160.^(2)
      val x3162 = x3161.>>>(16)
      val x3163 = x3161.^(x3162)
      val x3164 = x3163.*(-2048144789)
      val x3165 = x3164.>>>(13)
      val x3166 = x3164.^(x3165)
      val x3167 = x3166.*(-1028477387)
      val x3168 = x3167.>>>(16)
      val x3169 = x3167.^(x3168)
      x3169
    }
    override def cmp(x3171 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x3172 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      val x3173 = x3171._2
      val x3174 = x3172._2
      val x3175 = x3173.==(x3174)
      val x3179 = x3175.&&({
        val x3176 = x3171._3
        val x3177 = x3172._3
        val x3178 = x3176.==(x3177)
        x3178
      })
      val x3183 = x3179.&&({
        val x3180 = x3171._6
        val x3181 = x3172._6
        val x3182 = x3180.==(x3181)
        x3182
      })
      val x3184 = if(x3183) 
      {
        0
      }
      else
      {
        1
      }
      
      x3184
    }
  }
  val x3188 = Array[EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS]](SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx10, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx11)
  val x3189 = new Store[SEntry21_IIISSSSSSSSSTSDDDDIIS](2, x3188)
  x3189.index(0, IHash, true, -1)
  x3189.index(1, IHash, false, -1)
   object SEntry17_IIISSSSSSSSSSIIIS_Idx12 extends EntryIdx[SEntry17_IIISSSSSSSSSSIIIS] {
    override def hash(x3192 : SEntry17_IIISSSSSSSSSSIIIS) = {
      var x3193: Int = -889275714
      val x3194 = x3192._1
      val x3195 = x3194.hashCode()
      val x3196 = -862048943.*(x3195)
      val x3197 = x3196.<<(15)
      val x3198 = x3196.>>>(-15)
      val x3199 = x3197.|(x3198)
      val x3200 = x3199.*(461845907)
      val x3201 = x3193
      val x3202 = x3200.^(x3201)
      val x3203 = x3202.<<(13)
      val x3204 = x3202.>>>(-13)
      val x3205 = x3203.|(x3204)
      val x3206 = x3205.*(5)
      val x3207 = x3206.+(-430675100)
      x3193 = x3207
      val x3209 = x3192._2
      val x3210 = x3209.hashCode()
      val x3211 = -862048943.*(x3210)
      val x3212 = x3211.<<(15)
      val x3213 = x3211.>>>(-15)
      val x3214 = x3212.|(x3213)
      val x3215 = x3214.*(461845907)
      val x3216 = x3193
      val x3217 = x3215.^(x3216)
      val x3218 = x3217.<<(13)
      val x3219 = x3217.>>>(-13)
      val x3220 = x3218.|(x3219)
      val x3221 = x3220.*(5)
      val x3222 = x3221.+(-430675100)
      x3193 = x3222
      val x3224 = x3193
      val x3225 = x3224.^(2)
      val x3226 = x3225.>>>(16)
      val x3227 = x3225.^(x3226)
      val x3228 = x3227.*(-2048144789)
      val x3229 = x3228.>>>(13)
      val x3230 = x3228.^(x3229)
      val x3231 = x3230.*(-1028477387)
      val x3232 = x3231.>>>(16)
      val x3233 = x3231.^(x3232)
      x3233
    }
    override def cmp(x3235 : SEntry17_IIISSSSSSSSSSIIIS , x3236 : SEntry17_IIISSSSSSSSSSIIIS) = {
      val x3237 = x3235._1
      val x3238 = x3236._1
      val x3239 = x3237.==(x3238)
      val x3243 = x3239.&&({
        val x3240 = x3235._2
        val x3241 = x3236._2
        val x3242 = x3240.==(x3241)
        x3242
      })
      val x3244 = if(x3243) 
      {
        0
      }
      else
      {
        1
      }
      
      x3244
    }
  }
  val x3248 = Array[EntryIdx[SEntry17_IIISSSSSSSSSSIIIS]](SEntry17_IIISSSSSSSSSSIIIS_Idx12)
  val x3249 = new Store[SEntry17_IIISSSSSSSSSSIIIS](1, x3248)
  x3249.index(0, IHash, true, -1)
  
  val newOrderTbl = x2511
  val historyTbl = x2590
  val warehouseTbl = x2631
  val itemTbl = x2671
  val orderTbl = x2895
  val districtTbl = x2957
  val orderLineTbl = x3036
  val customerTbl = x3189
  val stockTbl = x3249
  val newOrderTxInst = new NewOrderTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
}
      
case class SEntry5_IISDS(var _1: Int, var _2: Int, var _3: String, var _4: Double, var _5: String) extends Entry(5) {def copy = SEntry5_IISDS(_1, _2, _3, _4, _5) }
case class SEntry8_IIIIITDS(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Int, var _6: Date, var _7: Double, var _8: String) extends Entry(8) {def copy = SEntry8_IIIIITDS(_1, _2, _3, _4, _5, _6, _7, _8) }
case class SEntry21_IIISSSSSSSSSTSDDDDIIS(var _1: Int, var _2: Int, var _3: Int, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: String, var _10: String, var _11: String, var _12: String, var _13: Date, var _14: String, var _15: Double, var _16: Double, var _17: Double, var _18: Double, var _19: Int, var _20: Int, var _21: String) extends Entry(21) {def copy = SEntry21_IIISSSSSSSSSTSDDDDIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21) }
case class SEntry9_ISSSSSSDD(var _1: Int, var _2: String, var _3: String, var _4: String, var _5: String, var _6: String, var _7: String, var _8: Double, var _9: Double) extends Entry(9) {def copy = SEntry9_ISSSSSSDD(_1, _2, _3, _4, _5, _6, _7, _8, _9) }
case class SEntry8_IIIITIIB(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Date, var _6: Int, var _7: Int, var _8: Boolean) extends Entry(8) {def copy = SEntry8_IIIITIIB(_1, _2, _3, _4, _5, _6, _7, _8) }
case class SEntry17_IIISSSSSSSSSSIIIS(var _1: Int, var _2: Int, var _3: Int, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: String, var _10: String, var _11: String, var _12: String, var _13: String, var _14: Int, var _15: Int, var _16: Int, var _17: String) extends Entry(17) {def copy = SEntry17_IIISSSSSSSSSSIIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) }
case class SEntry11_IISSSSSSDDI(var _1: Int, var _2: Int, var _3: String, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: Double, var _10: Double, var _11: Int) extends Entry(11) {def copy = SEntry11_IISSSSSSDDI(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) }
case class SEntry3_III(var _1: Int, var _2: Int, var _3: Int) extends Entry(3) {def copy = SEntry3_III(_1, _2, _3) }
case class SEntry10_IIIIIITIDS(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Int, var _6: Int, var _7: Date, var _8: Int, var _9: Double, var _10: String) extends Entry(10) {def copy = SEntry10_IIIIIITIDS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10) }
class DeliveryTx(x2511: Store[SEntry3_III], x2590: Store[SEntry8_IIIIITDS], x2631: Store[SEntry9_ISSSSSSDD], x2671: Store[SEntry5_IISDS], x2895: Store[SEntry8_IIIITIIB], x2957: Store[SEntry11_IISSSSSSDDI], x3036: Store[SEntry10_IIIIIITIDS], x3189: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x3249: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int) => Int) {
def apply(x10: Boolean, x11: Date, x12: Int, x13: Int) = {
  val x14 = new Array[Int](10)
  var x15: Int = 1
  while({
    val x16 = x15
    val x17 = x16.<=(10)
    x17
  })
  {
    val x22 = x15
    val x5818 = SEntry3_III(-1, x22, x12)
    val x26 = x2511.get(0, x5818)
    val x27 = x26.!=(null)
    if(x27) 
    {
      val x5823 = x26._1
      val x29 = x15
      val x30 = x29.-(1)
      x14.update(x30, x5823)
      x2511.delete(x26)
      val x33 = x15
      val x5829 = SEntry8_IIIITIIB(x5823, x33, x12, -1, null, -1, -1, false)
      val x36 = x2895.get(0, x5829)
      val x5832 = x36._4
      x36._6_=(x13)
      x2895.update(x36)
      var x40: Double = 0.0
      val x41 = x15
      val x5838 = SEntry10_IIIIIITIDS(x5823, x41, x12, -1, -1, -1, null, -1, -1.0, "")
      val x51 = { x44: SEntry10_IIIIIITIDS => {
          x44._7_=(x11)
          val x46 = x40
          val x5948 = x44._9
          val x48 = x46.+(x5948)
          x40 = x48
          x3036.update(x44)
          ()
        }
      }
      x3036.slice(0, x5838, x51)
      val x53 = x15
      val x5842 = SEntry21_IIISSSSSSSSSTSDDDDIIS(x5832, x53, x12, "", "", "", "", "", "", "", "", "", null, "", -1.0, -1.0, -1.0, -1.0, -1, -1, "")
      val x55 = x3189.get(0, x5842)
      val x56 = x40
      val x5845 = x55._17
      val x5846 = x5845.+(x56)
      x55._17_=(x5846)
      val x5848 = x55._20
      val x5849 = x5848.+(1)
      x55._20_=(x5849)
      x3189.update(x55)
      ()
    }
    else
    {
      val x60 = x15
      val x61 = x60.-(1)
      x14.update(x61, 0)
      ()
    }
    
    val x64 = x15
    val x65 = x64.+(1)
    x15 = x65
    ()
  }
  if(x10) 
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
    while({
      val x77 = x76
      val x78 = x77.<=(10)
      x78
    })
    {
      val x79 = x76
      val x80 = x79.-(1)
      val x81 = x14.apply(x80)
      val x82 = x81.>=(0)
      if(x82) 
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
        x74 = x96
        ()
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
        x74 = x106
        val x108 = x75
        val x109 = x108.+(1)
        x75 = x109
        ()
      }
      
      val x112 = x76
      val x113 = x112.+(1)
      x76 = x113
      ()
    }
    val x116 = x74
    val x117 = x116.+("+-----------------------------------------------------------------+\n\n")
    x74 = x117
    val x119 = x74
    println(x119)
    ()
  }
  else
  {
    ()
  }
  
  1
}
}
class StockLevelTx(x2511: Store[SEntry3_III], x2590: Store[SEntry8_IIIIITDS], x2631: Store[SEntry9_ISSSSSSDD], x2671: Store[SEntry5_IISDS], x2895: Store[SEntry8_IIIITIIB], x2957: Store[SEntry11_IISSSSSSDDI], x3036: Store[SEntry10_IIIIIITIDS], x3189: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x3249: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int) => Int) {
def apply(x122: Boolean, x123: Date, x124: Int, x125: Int, x126: Int, x127: Int) = {
  val x6136 = SEntry11_IISSSSSSDDI(x126, x125, "", "", "", "", "", "", -1.0, -1.0, -1)
  val x130 = x2957.get(0, x6136)
  val x6139 = x130._11
  val x132 = x6139.-(20)
  var x133: Int = x132
  val x134 = Set.apply[Int]()
  while({
    val x135 = x133
    val x136 = x135.<(x6139)
    x136
  })
  {
    val x137 = x133
    val x6148 = SEntry10_IIIIIITIDS(x137, x126, x125, -1, -1, -1, null, -1, -1.0, "")
    val x148 = { x140: SEntry10_IIIIIITIDS => {
        val x6180 = x140._5
        val x6181 = SEntry17_IIISSSSSSSSSSIIIS(x6180, x125, -1, "", "", "", "", "", "", "", "", "", "", -1, -1, -1, "")
        val x143 = x3249.get(0, x6181)
        val x6183 = x143._3
        val x145 = x6183.<(x127)
        if(x145) 
        {
          val x146 = x134.+=(x6180)
          ()
        }
        else
        {
          ()
        }
        
        ()
      }
    }
    x3036.slice(0, x6148, x148)
    val x150 = x133
    val x151 = x150.+(1)
    x133 = x151
    ()
  }
  val x154 = x134.size
  if(x122) 
  {
    val x155 = "\n+-------------------------- STOCK-LEVEL --------------------------+\n Warehouse: ".+(x125)
    val x156 = x155.+("\n District:  ")
    val x157 = x156.+(x126)
    val x158 = x157.+("\n\n Stock Level Threshold: ")
    val x159 = x158.+(x127)
    val x160 = x159.+("\n Low Stock Count:       ")
    val x161 = x160.+(x154)
    val x162 = x161.+("\n+-----------------------------------------------------------------+\n\n")
    println(x162)
    ()
  }
  else
  {
    ()
  }
  
  1
}
}
class OrderStatusTx(x2511: Store[SEntry3_III], x2590: Store[SEntry8_IIIIITDS], x2631: Store[SEntry9_ISSSSSSDD], x2671: Store[SEntry5_IISDS], x2895: Store[SEntry8_IIIITIIB], x2957: Store[SEntry11_IISSSSSSDDI], x3036: Store[SEntry10_IIIIIITIDS], x3189: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x3249: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int) {
def apply(x165: Boolean, x166: Date, x167: Int, x168: Int, x169: Int, x170: Int, x171: Int, x172: String) = {
  var x6239: SEntry21_IIISSSSSSSSSTSDDDDIIS = null
  val x174 = x170.>(0)
  if(x174) 
  {
    val x6242 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
    val x6244 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, x169, x168, "", "", x172, "", "", "", "", "", "", null, "", -1.0, -1.0, -1.0, -1.0, -1, -1, "")
    val x180 = { x178: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
        x6242.append(x178)
        ()
      }
    }
    x3189.slice(1, x6244, x180)
    val x182 = x6242.size
    val x183 = x182./(2)
    var x184: Int = x183
    val x185 = x6242.size
    val x186 = x185.%(2)
    val x187 = x186.==(0)
    if(x187) 
    {
      val x188 = x184
      val x189 = x188.-(1)
      x184 = x189
      ()
    }
    else
    {
      ()
    }
    
    val x198 = { (x192: SEntry21_IIISSSSSSSSSTSDDDDIIS, x193: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
        val x6298 = x192._4
        val x6299 = x193._4
        val x196 = x6298.compareToIgnoreCase(x6299)
        val x197 = x196.<(0)
        x197
      }
    }
    val x199 = x6242.sortWith(x198)
    val x200 = x184
    val x201 = x199.apply(x200)
    x6239 = x201
    ()
  }
  else
  {
    val x6262 = SEntry21_IIISSSSSSSSSTSDDDDIIS(x171, x169, x168, "", "", "", "", "", "", "", "", "", null, "", -1.0, -1.0, -1.0, -1.0, -1, -1, "")
    val x205 = x3189.get(0, x6262)
    x6239 = x205
    ()
  }
  
  val x208 = x6239
  val x6267 = x208._3
  var x218: Int = 0
  1
}
}
class PaymentTx(x2511: Store[SEntry3_III], x2590: Store[SEntry8_IIIIITDS], x2631: Store[SEntry9_ISSSSSSDD], x2671: Store[SEntry5_IISDS], x2895: Store[SEntry8_IIIITIIB], x2957: Store[SEntry11_IISSSSSSDDI], x3036: Store[SEntry10_IIIIIITIDS], x3189: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x3249: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int) {
def apply(x219: Boolean, x220: Date, x221: Int, x222: Int, x223: Int, x224: Int, x225: Int, x226: Int, x227: Int, x228: String, x229: Double) = {
  val x6367 = SEntry9_ISSSSSSDD(x222, "", "", "", "", "", "", -1.0, -1.0)
  val x232 = x2631.get(0, x6367)
  val x6370 = x232._9
  val x6371 = x6370.+(x229)
  x232._9_=(x6371)
  x2631.update(x232)
  val x6374 = SEntry11_IISSSSSSDDI(x223, x222, "", "", "", "", "", "", -1.0, -1.0, -1)
  val x237 = x2957.get(0, x6374)
  val x6377 = x237._10
  val x6378 = x6377.+(x229)
  x237._10_=(x6378)
  x2957.update(x237)
  var x6381: SEntry21_IIISSSSSSSSSTSDDDDIIS = null
  val x241 = x224.>(0)
  if(x241) 
  {
    val x6384 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
    val x6386 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, x226, x225, "", "", x228, "", "", "", "", "", "", null, "", -1.0, -1.0, -1.0, -1.0, -1, -1, "")
    val x247 = { x245: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
        x6384.append(x245)
        ()
      }
    }
    x3189.slice(1, x6386, x247)
    val x249 = x6384.size
    val x250 = x249./(2)
    var x251: Int = x250
    val x252 = x6384.size
    val x253 = x252.%(2)
    val x254 = x253.==(0)
    if(x254) 
    {
      val x255 = x251
      val x256 = x255.-(1)
      x251 = x256
      ()
    }
    else
    {
      ()
    }
    
    val x265 = { (x259: SEntry21_IIISSSSSSSSSTSDDDDIIS, x260: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
        val x6495 = x259._4
        val x6496 = x260._4
        val x263 = x6495.compareToIgnoreCase(x6496)
        val x264 = x263.<(0)
        x264
      }
    }
    val x266 = x6384.sortWith(x265)
    val x267 = x251
    val x268 = x266.apply(x267)
    x6381 = x268
    ()
  }
  else
  {
    val x6404 = SEntry21_IIISSSSSSSSSTSDDDDIIS(x227, x226, x225, "", "", "", "", "", "", "", "", "", null, "", -1.0, -1.0, -1.0, -1.0, -1, -1, "")
    val x272 = x3189.get(0, x6404)
    x6381 = x272
    ()
  }
  
  val x275 = x6381
  val x6409 = x275._21
  var x277: String = x6409
  val x278 = x6381
  val x6412 = x278._14
  val x280 = x6412.contains("BC")
  if(x280) 
  {
    val x281 = x6381
    val x6416 = x281._1
    val x283 = x277
    val x285 = "%d %d %d %d %d $%f %s | %s".format(x6416,x226,x225,x223,x222,x229,x220,x283)
    x277 = x285
    val x287 = x277
    val x288 = x287.length
    val x289 = x288.>(500)
    if(x289) 
    {
      val x290 = x277
      val x291 = x290.substring(0, 500)
      x277 = x291
      ()
    }
    else
    {
      ()
    }
    
    val x294 = x6381
    val x6429 = x294._17
    val x6430 = x6429.+(x229)
    x294._17_=(x6430)
    val x296 = x6381
    val x297 = x277
    x296._21_=(x297)
    ()
  }
  else
  {
    val x299 = x6381
    val x6436 = x299._17
    val x6437 = x6436.+(x229)
    x299._17_=(x6437)
    ()
  }
  
  val x302 = x6381
  x3189.update(x302)
  val x6441 = x232._2
  val x6442 = x237._3
  val x306 = x6441.length
  val x307 = x306.>(10)
  val x309 = if(x307) 
  {
    val x308 = x6441.substring(0, 10)
    x308
  }
  else
  {
    x6441
  }
  
  val x310 = x309.+("    ")
  val x311 = x6442.length
  val x312 = x311.>(10)
  val x314 = if(x312) 
  {
    val x313 = x6442.substring(0, 10)
    x313
  }
  else
  {
    x6442
  }
  
  val x315 = x310.+(x314)
  val x316 = x6381
  val x6454 = x316._1
  val x6456 = SEntry8_IIIIITDS(x6454, x226, x225, x223, x222, x220, x229, x315)
  x2590.insert(x6456)
  1
}
}
class NewOrderTx(x2511: Store[SEntry3_III], x2590: Store[SEntry8_IIIIITDS], x2631: Store[SEntry9_ISSSSSSDD], x2671: Store[SEntry5_IISDS], x2895: Store[SEntry8_IIIITIIB], x2957: Store[SEntry11_IISSSSSSDDI], x3036: Store[SEntry10_IIIIIITIDS], x3189: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x3249: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int) {
def apply(x321: Boolean, x322: Date, x323: Int, x324: Int, x325: Int, x326: Int, x327: Int, x328: Int, x329: Array[Int], x330: Array[Int], x331: Array[Int], x332: Array[Double], x333: Array[String], x334: Array[Int], x335: Array[String], x336: Array[Double]) = {
  if(x321) 
  {
    val x338 = "Started NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(x324,x325,x326)
    println(x338)
    ()
  }
  else
  {
    ()
  }
  
  var x341: Int = 0
  var x342: Boolean = false
  val x343 = new Array[String](x327)
  var x344: Boolean = true
  while({
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
    val x6671 = SEntry5_IISDS(x350, -1, "", -1.0, "")
    val x353 = x2671.get(0, x6671)
    val x354 = x353.==(null)
    if(x354) 
    {
      x344 = false
      ()
    }
    else
    {
      val x356 = x341
      val x6678 = x353._3
      x333.update(x356, x6678)
      val x359 = x341
      val x6681 = x353._4
      x332.update(x359, x6681)
      val x362 = x341
      val x6684 = x353._5
      x343.update(x362, x6684)
      ()
    }
    
    val x366 = x341
    val x367 = x366.+(1)
    x341 = x367
    ()
  }
  val x370 = x344
  if(x370) 
  {
    val x6691 = SEntry21_IIISSSSSSSSSTSDDDDIIS(x326, x325, x324, "", "", "", "", "", "", "", "", "", null, "", -1.0, -1.0, -1.0, -1.0, -1, -1, "")
    val x373 = x3189.get(0, x6691)
    val x6694 = SEntry9_ISSSSSSDD(x324, "", "", "", "", "", "", -1.0, -1.0)
    val x376 = x2631.get(0, x6694)
    val x6697 = SEntry11_IISSSSSSDDI(x325, x324, "", "", "", "", "", "", -1.0, -1.0, -1)
    val x379 = x2957.get(0, x6697)
    val x6700 = x379._11
    val x6701 = x379._11
    val x6702 = x6701.+(1)
    x379._11_=(x6702)
    x2957.update(x379)
    val x383 = x328.>(0)
    val x6707 = SEntry8_IIIITIIB(x6700, x325, x324, x326, x322, -1, x327, x383)
    x2895.insert(x6707)
    val x6710 = SEntry3_III(x6700, x325, x324)
    x2511.insert(x6710)
    var x390: Double = 0.0
    x341 = 0
    while({
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
      val x6723 = SEntry17_IIISSSSSSSSSSIIIS(x397, x395, -1, "", "", "", "", "", "", "", "", "", "", -1, -1, -1, "")
      val x401 = x3249.get(0, x6723)
      val x402 = x325.==(1)
      val x429 = if(x402) 
      {
        val x6727 = x401._4
        x6727
      }
      else
      {
        val x404 = x325.==(2)
        val x428 = if(x404) 
        {
          val x6730 = x401._5
          x6730
        }
        else
        {
          val x406 = x325.==(3)
          val x427 = if(x406) 
          {
            val x6733 = x401._6
            x6733
          }
          else
          {
            val x408 = x325.==(4)
            val x426 = if(x408) 
            {
              val x6736 = x401._7
              x6736
            }
            else
            {
              val x410 = x325.==(5)
              val x425 = if(x410) 
              {
                val x6739 = x401._8
                x6739
              }
              else
              {
                val x412 = x325.==(6)
                val x424 = if(x412) 
                {
                  val x6742 = x401._9
                  x6742
                }
                else
                {
                  val x414 = x325.==(7)
                  val x423 = if(x414) 
                  {
                    val x6745 = x401._10
                    x6745
                  }
                  else
                  {
                    val x416 = x325.==(8)
                    val x422 = if(x416) 
                    {
                      val x6748 = x401._11
                      x6748
                    }
                    else
                    {
                      val x418 = x325.==(9)
                      val x421 = if(x418) 
                      {
                        val x6751 = x401._12
                        x6751
                      }
                      else
                      {
                        val x6752 = x401._13
                        x6752
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
      
      val x6753 = x401._3
      val x431 = x341
      x334.update(x431, x6753)
      val x6756 = x373._14
      val x434 = x6756.contains("original")
      val x437 = x434.&&({
        val x6759 = x401._17
        val x436 = x6759.contains("original")
        x436
      })
      if(x437) 
      {
        val x438 = x341
        x335.update(x438, "B")
        ()
      }
      else
      {
        val x440 = x341
        x335.update(x440, "G")
        ()
      }
      
      val x443 = x6753.-(x399)
      x401._3_=(x443)
      val x445 = x6753.<=(x399)
      if(x445) 
      {
        val x6770 = x401._3
        val x6771 = x6770.+(91)
        x401._3_=(x6771)
        ()
      }
      else
      {
        ()
      }
      
      var x448: Int = 0
      val x449 = x395.!=(x324)
      if(x449) 
      {
        x448 = 1
        ()
      }
      else
      {
        ()
      }
      
      x3249.update(x401)
      val x6778 = x373._16
      val x6779 = x376._8
      val x6780 = x379._9
      val x456 = x341
      val x457 = x332.apply(x456)
      val x458 = x399.toDouble
      val x459 = x458.*(x457)
      val x460 = 1.0.+(x6779)
      val x461 = x460.+(x6780)
      val x462 = x459.*(x461)
      val x463 = 1.0.-(x6778)
      val x464 = x462.*(x463)
      val x465 = x341
      x336.update(x465, x464)
      val x467 = x390
      val x468 = x467.+(x464)
      x390 = x468
      val x470 = x341
      val x471 = x470.+(1)
      val x6798 = SEntry10_IIIIIITIDS(x6700, x325, x324, x471, x397, x395, null, x399, x464, x429)
      x3036.insert(x6798)
      val x475 = x341
      val x476 = x475.+(1)
      x341 = x476
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
