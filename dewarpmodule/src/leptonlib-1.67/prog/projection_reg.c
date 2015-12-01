/*====================================================================*
 -  Copyright (C) 2001 Leptonica.  All rights reserved.
 -  This software is distributed in the hope that it will be
 -  useful, but with NO WARRANTY OF ANY KIND.
 -  No author or distributor accepts responsibility to anyone for the
 -  consequences of using this software, or for whether it serves any
 -  particular purpose or works at all, unless he or she says so in
 -  writing.  Everyone is granted permission to copy, modify and
 -  redistribute this source code, for commercial or non-commercial
 -  purposes, with the following restrictions: (1) the origin of this
 -  source code must not be misrepresented; (2) modified versions must
 -  be plainly marked as such; and (3) this notice may not be removed
 -  or altered from any source or modified source distribution.
 *====================================================================*/

/*
 *  projection_reg.c
 *
 *    Tests projection stats for rows and columns.
 *    Just for interest, a number of different tests are done.
 */

#ifndef  _WIN32
#include <unistd.h>
#else
    /* Need declaration of Sleep() defined in WinBase.h, but must
     * include Windows.h to avoid errors  */
#include <Windows.h>
#endif  /* _WIN32 */
#include "allheaders.h"

void TestProjection(PIX *pixs, l_int32 *pcount, L_REGPARAMS *rp,
                    l_int32 display);

main(int    argc,
     char **argv)
{
l_int32       count, success, display;
FILE         *fp;
PIX          *pixs, *pixg1, *pixg2;
L_REGPARAMS  *rp;

    if (regTestSetup(argc, argv, &fp, &display, &success, &rp))
	return 1;

        /* Use for input two different images */
    pixs = pixRead("projectionstats.jpg");
    pixg1 = pixConvertTo8(pixs, 0);
    pixDestroy(&pixs);
    pixs = pixRead("feyn.tif");
    pixg2 = pixScaleToGray4(pixs);
    pixDestroy(&pixs);

    count = 0;
    TestProjection(pixg1, &count, rp, display);
    TestProjection(pixg2, &count, rp, display);
    pixDestroy(&pixg1);
    pixDestroy(&pixg2);
    regTestCleanup(argc, argv, fp, success, rp);
    return 0;
}


/*
 *  Test both vertical and horizontal projections on this image.
 *  We rotate the image by 90 degrees for the horizontal projection,
 *  so that the two results should be identical.
 */
void
TestProjection(PIX          *pixs,
               l_int32      *pcount,
               L_REGPARAMS  *rp,
               l_int32       display)
{
l_int32  outline;
NUMA    *na1, *na2, *na3, *na4, *na5, *na6;
NUMA    *na7, *na8, *na9, *na10, *na11, *na12;
PIX     *pixd, *pixt;
PIXA    *pixa;

    outline = 2;
    pixColumnStats(pixs, &na1, &na3, &na5, &na7, &na9, &na11);
    pixd = pixRotateOrth(pixs, 1);
    pixRowStats(pixd, &na2, &na4, &na6, &na8, &na10, &na12);

        /* The png plot files are written to "/tmp/proj.0.png", etc.
         * These temp files are overwritten each time this
         * function is called. */
    gplotSimple1(na1, GPLOT_PNG, "/tmp/proj.0", "Mean value");
    gplotSimple1(na2, GPLOT_PNG, "/tmp/proj.1", "Mean value");
    gplotSimple1(na3, GPLOT_PNG, "/tmp/proj.2", "Median value");
    gplotSimple1(na4, GPLOT_PNG, "/tmp/proj.3", "Median value");
    gplotSimple1(na5, GPLOT_PNG, "/tmp/proj.4", "Mode value");
    gplotSimple1(na6, GPLOT_PNG, "/tmp/proj.5", "Mode value");
    gplotSimple1(na7, GPLOT_PNG, "/tmp/proj.6", "Mode count");
    gplotSimple1(na8, GPLOT_PNG, "/tmp/proj.7", "Mode count");
    gplotSimple1(na9, GPLOT_PNG, "/tmp/proj.8", "Variance");
    gplotSimple1(na10, GPLOT_PNG, "/tmp/proj.9", "Variance");
    gplotSimple1(na11, GPLOT_PNG, "/tmp/proj.10", "Square Root Variance");
    gplotSimple1(na12, GPLOT_PNG, "/tmp/proj.11", "Square Root Variance");
    sleep(1);

        /* Each of the 12 plot files is read into a pix and then:
         *    (1) saved into a pixa for display
         *    (2) saved as a golden file (generate stage) or compared
         *        to the existing golden file (testing stage)    */
    pixa = pixaCreate(13);
    pixSaveTiledOutline(pixs, pixa, 1, 1, 30, outline, 32);
    pixt = pixRead("/tmp/proj.0.png");
    regTestWritePixAndCheck(pixt, IFF_PNG, pcount, rp);
    pixSaveTiledOutline(pixt, pixa, 1, 1, 30, outline, 32);
    pixDestroy(&pixt);
    pixt = pixRead("/tmp/proj.1.png");
    regTestWritePixAndCheck(pixt, IFF_PNG, pcount, rp);
    pixSaveTiledOutline(pixt, pixa, 1, 0, 30, outline, 32);
    pixDestroy(&pixt);
    pixt = pixRead("/tmp/proj.2.png");
    regTestWritePixAndCheck(pixt, IFF_PNG, pcount, rp);
    pixSaveTiledOutline(pixt, pixa, 1, 1, 30, outline, 32);
    pixDestroy(&pixt);
    pixt = pixRead("/tmp/proj.3.png");
    regTestWritePixAndCheck(pixt, IFF_PNG, pcount, rp);
    pixSaveTiledOutline(pixt, pixa, 1, 0, 30, outline, 32);
    pixDestroy(&pixt);
    pixt = pixRead("/tmp/proj.4.png");
    regTestWritePixAndCheck(pixt, IFF_PNG, pcount, rp);
    pixSaveTiledOutline(pixt, pixa, 1, 1, 30, outline, 32);
    pixDestroy(&pixt);
    pixt = pixRead("/tmp/proj.5.png");
    regTestWritePixAndCheck(pixt, IFF_PNG, pcount, rp);
    pixSaveTiledOutline(pixt, pixa, 1, 0, 30, outline, 32);
    pixDestroy(&pixt);
    pixt = pixRead("/tmp/proj.6.png");
    regTestWritePixAndCheck(pixt, IFF_PNG, pcount, rp);
    pixSaveTiledOutline(pixt, pixa, 1, 1, 30, outline, 32);
    pixDestroy(&pixt);
    pixt = pixRead("/tmp/proj.7.png");
    regTestWritePixAndCheck(pixt, IFF_PNG, pcount, rp);
    pixSaveTiledOutline(pixt, pixa, 1, 0, 30, outline, 32);
    pixDestroy(&pixt);
    pixt = pixRead("/tmp/proj.8.png");
    regTestWritePixAndCheck(pixt, IFF_PNG, pcount, rp);
    pixSaveTiledOutline(pixt, pixa, 1, 1, 30, outline, 32);
    pixDestroy(&pixt);
    pixt = pixRead("/tmp/proj.9.png");
    regTestWritePixAndCheck(pixt, IFF_PNG, pcount, rp);
    pixSaveTiledOutline(pixt, pixa, 1, 0, 30, outline, 32);
    pixDestroy(&pixt);
    pixt = pixRead("/tmp/proj.10.png");
    regTestWritePixAndCheck(pixt, IFF_PNG, pcount, rp);
    pixSaveTiledOutline(pixt, pixa, 1, 1, 30, outline, 32);
    pixDestroy(&pixt);
    pixt = pixRead("/tmp/proj.11.png");
    regTestWritePixAndCheck(pixt, IFF_PNG, pcount, rp);
    pixSaveTiledOutline(pixt, pixa, 1, 0, 30, outline, 32);
    pixDestroy(&pixt);

        /* The pixa is composited into a pix and 'goldened'/tested */
    pixt = pixaDisplay(pixa, 0, 0);
    regTestWritePixAndCheck(pixt, IFF_PNG, pcount, rp);
    pixDisplayWithTitle(pixt, 100, 0, NULL, display);
    pixDestroy(&pixt);
    pixaDestroy(&pixa);

        /* The 12 plot files are tested in pairs for identity */
    regTestCompareFiles(rp->fp, rp->argv, 0, 1, &rp->success);
    regTestCompareFiles(rp->fp, rp->argv, 2, 3, &rp->success);
    regTestCompareFiles(rp->fp, rp->argv, 4, 5, &rp->success);
    regTestCompareFiles(rp->fp, rp->argv, 6, 7, &rp->success);
    regTestCompareFiles(rp->fp, rp->argv, 8, 9, &rp->success);
    regTestCompareFiles(rp->fp, rp->argv, 10, 11, &rp->success);

    pixDestroy(&pixd);
    numaDestroy(&na1);
    numaDestroy(&na2);
    numaDestroy(&na3);
    numaDestroy(&na4);
    numaDestroy(&na5);
    numaDestroy(&na6);
    numaDestroy(&na7);
    numaDestroy(&na8);
    numaDestroy(&na9);
    numaDestroy(&na10);
    numaDestroy(&na11);
    numaDestroy(&na12);
    return;
}


