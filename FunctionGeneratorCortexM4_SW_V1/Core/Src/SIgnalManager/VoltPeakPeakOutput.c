/*
 * VoltPeakPeakOutput.c
 *
 *  Created on: 14 May 2020
 *      Author: chris
 */

#include "VoltPeakPeakOutput.h"
#include "DisplayManager.h"


#include "dac.h"

//#define AMP_OFFSET 20   // gain 4
#define AMP_OFFSET 20   // gain 5
#define AMP_OFFSET50 AMP_OFFSET+50
#define AMP_OFFSET60 AMP_OFFSET+60
#define AMP_OFFSET70 AMP_OFFSET+70
#define AMP_OFFSET80 AMP_OFFSET+80
#define AMP_OFFSET90 AMP_OFFSET+90
#define AMP_OFFSET100 AMP_OFFSET+100




/*
 * 		Array of Vpp presets
 */
AmplitudeProfile_t theAmpProfiles[MAX_VPP_PRESETS] =
{
/*
		{	VPP01	,	0.1	,	7	,	"+ 40.00 dBmV"	,	0.005	,	AMP_OFFSET	,	392	},
		{	VPP02	,	0.2	,	7	,	"+ 46.00 dBmV"	,	0.011	,	AMP_OFFSET	,	388	},
		{	VPP03	,	0.3	,	7	,	"+ 49.50 dBmV"	,	0.016	,	AMP_OFFSET	,	384	},
		{	VPP04	,	0.4	,	7	,	"+ 52.00 dBmV"	,	0.021	,	AMP_OFFSET	,	380	},
		{	VPP05	,	0.5	,	7	,	"+ 54.00 dBmV"	,	0.026	,	AMP_OFFSET	,	376	},
		{	VPP06	,	0.6	,	7	,	"+ 55.60 dBmV"	,	0.032	,	AMP_OFFSET	,	372	},
		{	VPP07	,	0.7	,	7	,	"+ 56.90 dBmV"	,	0.037	,	AMP_OFFSET	,	368	},
		{	VPP08	,	0.8	,	7	,	"+ 58.10 dBmV"	,	0.042	,	AMP_OFFSET	,	364	},
		{	VPP09	,	0.9	,	7	,	"+ 59.10 dBmV"	,	0.048	,	AMP_OFFSET	,	360	},
		{	VPP10	,	1.0	,	7	,	"+ 60.00 dBmV"	,	0.053	,	AMP_OFFSET	,	356	},
		{	VPP11	,	1.1	,	7	,	"+ 60.80 dBmV"	,	0.058	,	AMP_OFFSET	,	352	},
		{	VPP12	,	1.2	,	7	,	"+ 61.60 dBmV"	,	0.063	,	AMP_OFFSET	,	348	},
		{	VPP13	,	1.3	,	7	,	"+ 62.30 dBmV"	,	0.069	,	AMP_OFFSET	,	344	},
		{	VPP14	,	1.4	,	7	,	"+ 62.90 dBmV"	,	0.074	,	AMP_OFFSET	,	340	},
		{	VPP15	,	1.5	,	7	,	"+ 63.50 dBmV"	,	0.079	,	AMP_OFFSET	,	336	},
		{	VPP16	,	1.6	,	7	,	"+ 64.10 dBmV"	,	0.085	,	AMP_OFFSET	,	332	},
		{	VPP17	,	1.7	,	7	,	"+ 64.60 dBmV"	,	0.090	,	AMP_OFFSET	,	328	},
		{	VPP18	,	1.8	,	7	,	"+ 65.10 dBmV"	,	0.095	,	AMP_OFFSET	,	324	},
		{	VPP19	,	1.9	,	7	,	"+ 65.60 dBmV"	,	0.101	,	AMP_OFFSET	,	320	},
		{	VPP20	,	2.0	,	7	,	"+ 66.00 dBmV"	,	0.106	,	AMP_OFFSET	,	316	},
		{	VPP21	,	2.1	,	7	,	"+ 66.40 dBmV"	,	0.111	,	AMP_OFFSET	,	312	},
		{	VPP22	,	2.2	,	7	,	"+ 66.80 dBmV"	,	0.116	,	AMP_OFFSET	,	308	},
		{	VPP23	,	2.3	,	7	,	"+ 67.20 dBmV"	,	0.122	,	AMP_OFFSET	,	304	},
		{	VPP24	,	2.4	,	7	,	"+ 67.60 dBmV"	,	0.127	,	AMP_OFFSET	,	300	},
		{	VPP25	,	2.5	,	7	,	"+ 68.00 dBmV"	,	0.132	,	AMP_OFFSET	,	296	},
		{	VPP26	,	2.6	,	7	,	"+ 68.30 dBmV"	,	0.138	,	AMP_OFFSET	,	292	},
		{	VPP27	,	2.7	,	7	,	"+ 68.60 dBmV"	,	0.143	,	AMP_OFFSET	,	288	},
		{	VPP28	,	2.8	,	7	,	"+ 68.90 dBmV"	,	0.148	,	AMP_OFFSET	,	284	},
		{	VPP29	,	2.9	,	7	,	"+ 69.20 dBmV"	,	0.153	,	AMP_OFFSET	,	280	},
		{	VPP30	,	3.0	,	7	,	"+ 69.50 dBmV"	,	0.159	,	AMP_OFFSET	,	276	},
		{	VPP31	,	3.1	,	7	,	"+ 69.80 dBmV"	,	0.164	,	AMP_OFFSET	,	272	},
		{	VPP32	,	3.2	,	7	,	"+ 70.10 dBmV"	,	0.169	,	AMP_OFFSET	,	268	},
		{	VPP33	,	3.3	,	7	,	"+ 70.40 dBmV"	,	0.175	,	AMP_OFFSET	,	264	},
		{	VPP34	,	3.4	,	7	,	"+ 70.60 dBmV"	,	0.180	,	AMP_OFFSET	,	260	},
		{	VPP35	,	3.5	,	7	,	"+ 70.90 dBmV"	,	0.185	,	AMP_OFFSET	,	256	},
		{	VPP36	,	3.6	,	7	,	"+ 71.10 dBmV"	,	0.190	,	AMP_OFFSET	,	252	},
		{	VPP37	,	3.7	,	7	,	"+ 71.40 dBmV"	,	0.196	,	AMP_OFFSET	,	248	},
		{	VPP38	,	3.8	,	7	,	"+ 71.60 dBmV"	,	0.201	,	AMP_OFFSET	,	244	},
		{	VPP39	,	3.9	,	7	,	"+ 71.80 dBmV"	,	0.206	,	AMP_OFFSET	,	240	},
		{	VPP40	,	4.0	,	7	,	"+ 72.00 dBmV"	,	0.212	,	AMP_OFFSET	,	236	},
		{	VPP41	,	4.1	,	7	,	"+ 72.30 dBmV"	,	0.217	,	AMP_OFFSET	,	232	},
		{	VPP42	,	4.2	,	7	,	"+ 72.50 dBmV"	,	0.222	,	AMP_OFFSET	,	228	},
		{	VPP43	,	4.3	,	7	,	"+ 72.70 dBmV"	,	0.228	,	AMP_OFFSET	,	224	},
		{	VPP44	,	4.4	,	7	,	"+ 72.90 dBmV"	,	0.233	,	AMP_OFFSET	,	220	},
		{	VPP45	,	4.5	,	7	,	"+ 73.10 dBmV"	,	0.238	,	AMP_OFFSET	,	216	},
		{	VPP46	,	4.6	,	7	,	"+ 73.30 dBmV"	,	0.243	,	AMP_OFFSET	,	212	},
		{	VPP47	,	4.7	,	7	,	"+ 73.40 dBmV"	,	0.249	,	AMP_OFFSET	,	208	},
		{	VPP48	,	4.8	,	7	,	"+ 73.60 dBmV"	,	0.254	,	AMP_OFFSET	,	204	},
		{	VPP49	,	4.9	,	7	,	"+ 73.80 dBmV"	,	0.259	,	AMP_OFFSET	,	200	},
		{	VPP50	,	5.0	,	7	,	"+ 74.00 dBmV"	,	0.265	,	AMP_OFFSET	,	196	},
		{	VPP51	,	5.1	,	7	,	"+ 74.20 dBmV"	,	0.270	,	AMP_OFFSET	,	192	},
		{	VPP52	,	5.2	,	7	,	"+ 74.30 dBmV"	,	0.275	,	AMP_OFFSET	,	188	},
		{	VPP53	,	5.3	,	7	,	"+ 74.50 dBmV"	,	0.280	,	AMP_OFFSET	,	184	},
		{	VPP54	,	5.4	,	7	,	"+ 74.60 dBmV"	,	0.286	,	AMP_OFFSET	,	180	},
		{	VPP55	,	5.5	,	7	,	"+ 74.80 dBmV"	,	0.291	,	AMP_OFFSET	,	176	},
		{	VPP56	,	5.6	,	7	,	"+ 75.00 dBmV"	,	0.296	,	AMP_OFFSET	,	172	},
		{	VPP57	,	5.7	,	7	,	"+ 75.10 dBmV"	,	0.302	,	AMP_OFFSET	,	168	},
		{	VPP58	,	5.8	,	7	,	"+ 75.30 dBmV"	,	0.307	,	AMP_OFFSET	,	164	},
		{	VPP59	,	5.9	,	7	,	"+ 75.40 dBmV"	,	0.312	,	AMP_OFFSET	,	160	},
		{	VPP60	,	6.0	,	7	,	"+ 75.60 dBmV"	,	0.317	,	AMP_OFFSET	,	156	},
		{	VPP61	,	6.1	,	7	,	"+ 75.70 dBmV"	,	0.323	,	AMP_OFFSET	,	152	},
		{	VPP62	,	6.2	,	7	,	"+ 75.80 dBmV"	,	0.328	,	AMP_OFFSET	,	148	},
		{	VPP63	,	6.3	,	7	,	"+ 76.00 dBmV"	,	0.333	,	AMP_OFFSET	,	144	},
		{	VPP64	,	6.4	,	7	,	"+ 76.10 dBmV"	,	0.339	,	AMP_OFFSET	,	140	},
		{	VPP65	,	6.5	,	7	,	"+ 76.30 dBmV"	,	0.344	,	AMP_OFFSET	,	136	},
		{	VPP66	,	6.6	,	7	,	"+ 76.40 dBmV"	,	0.349	,	AMP_OFFSET	,	132	},
		{	VPP67	,	6.7	,	7	,	"+ 76.50 dBmV"	,	0.354	,	AMP_OFFSET	,	128	},
		{	VPP68	,	6.8	,	7	,	"+ 76.70 dBmV"	,	0.360	,	AMP_OFFSET	,	124	},
		{	VPP69	,	6.9	,	7	,	"+ 76.80 dBmV"	,	0.365	,	AMP_OFFSET	,	120	},
		{	VPP70	,	7.0	,	7	,	"+ 76.90 dBmV"	,	0.370	,	AMP_OFFSET	,	116	},
		{	VPP71	,	7.1	,	7	,	"+ 77.00 dBmV"	,	0.376	,	AMP_OFFSET	,	112	},
		{	VPP72	,	7.2	,	7	,	"+ 77.10 dBmV"	,	0.381	,	AMP_OFFSET	,	108	},
		{	VPP73	,	7.3	,	7	,	"+ 77.30 dBmV"	,	0.386	,	AMP_OFFSET	,	104	},
		{	VPP74	,	7.4	,	7	,	"+ 77.40 dBmV"	,	0.392	,	AMP_OFFSET	,	100	},
		{	VPP75	,	7.5	,	7	,	"+ 77.50 dBmV"	,	0.397	,	AMP_OFFSET	,	96	},
		{	VPP76	,	7.6	,	7	,	"+ 77.60 dBmV"	,	0.402	,	AMP_OFFSET	,	92	},
		{	VPP77	,	7.7	,	7	,	"+ 77.70 dBmV"	,	0.407	,	AMP_OFFSET	,	88	},
		{	VPP78	,	7.8	,	7	,	"+ 77.80 dBmV"	,	0.413	,	AMP_OFFSET	,	84	},
		{	VPP79	,	7.9	,	7	,	"+ 78.00 dBmV"	,	0.418	,	AMP_OFFSET	,	80	},
		{	VPP80	,	8.0	,	7	,	"+ 78.10 dBmV"	,	0.423	,	AMP_OFFSET	,	76	},
		{	VPP81	,	8.1	,	7	,	"+ 78.20 dBmV"	,	0.429	,	AMP_OFFSET	,	72	},
		{	VPP82	,	8.2	,	7	,	"+ 78.30 dBmV"	,	0.434	,	AMP_OFFSET	,	68	},
		{	VPP83	,	8.3	,	7	,	"+ 78.40 dBmV"	,	0.439	,	AMP_OFFSET	,	64	},
		{	VPP84	,	8.4	,	7	,	"+ 78.50 dBmV"	,	0.444	,	AMP_OFFSET	,	60	},
		{	VPP85	,	8.5	,	7	,	"+ 78.60 dBmV"	,	0.450	,	AMP_OFFSET	,	56	},
		{	VPP86	,	8.6	,	7	,	"+ 78.70 dBmV"	,	0.455	,	AMP_OFFSET	,	52	},
		{	VPP87	,	8.7	,	7	,	"+ 78.80 dBmV"	,	0.460	,	AMP_OFFSET	,	48	},
		{	VPP88	,	8.8	,	7	,	"+ 78.90 dBmV"	,	0.466	,	AMP_OFFSET	,	44	},
		{	VPP89	,	8.9	,	7	,	"+ 79.00 dBmV"	,	0.471	,	AMP_OFFSET	,	40	},
		{	VPP90	,	9.0	,	7	,	"+ 79.10 dBmV"	,	0.476	,	AMP_OFFSET	,	36	},
		{	VPP91	,	9.1	,	7	,	"+ 79.20 dBmV"	,	0.481	,	AMP_OFFSET	,	32	},
		{	VPP92	,	9.2	,	7	,	"+ 79.30 dBmV"	,	0.487	,	AMP_OFFSET	,	28	},
		{	VPP93	,	9.3	,	7	,	"+ 79.40 dBmV"	,	0.492	,	AMP_OFFSET	,	24	},
		{	VPP94	,	9.4	,	7	,	"+ 79.50 dBmV"	,	0.497	,	AMP_OFFSET	,	20	},
		{	VPP95	,	9.5	,	7	,	"+ 79.60 dBmV"	,	0.503	,	AMP_OFFSET	,	16	},
		{	VPP96	,	9.6	,	7	,	"+ 79.60 dBmV"	,	0.508	,	AMP_OFFSET	,	12	},
		{	VPP97	,	9.7	,	7	,	"+ 79.70 dBmV"	,	0.513	,	AMP_OFFSET	,	8	},
		{	VPP98	,	9.8	,	7	,	"+ 79.80 dBmV"	,	0.519	,	AMP_OFFSET	,	4	}
		*/

		{	VPP01	,	0.1	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	392	},
		{	VPP02	,	0.2	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	388	},
		{	VPP03	,	0.3	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	384	},
		{	VPP04	,	0.4	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	380	},
		{	VPP05	,	0.5	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	376	},
		{	VPP06	,	0.6	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	372	},
		{	VPP07	,	0.7	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	368	},
		{	VPP08	,	0.8	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	364	},
		{	VPP09	,	0.9	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	360	},
		{	VPP10	,	1.0	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	356	},
		{	VPP11	,	1.1	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	352	},
		{	VPP12	,	1.2	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	348	},
		{	VPP13	,	1.3	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	344	},
		{	VPP14	,	1.4	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	340	},
		{	VPP15	,	1.5	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	336	},
		{	VPP16	,	1.6	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	332	},
		{	VPP17	,	1.7	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	328	},
		{	VPP18	,	1.8	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	324	},
		{	VPP19	,	1.9	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	320	},
		{	VPP20	,	2.0	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	316	},
		{	VPP21	,	2.1	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	312	},
		{	VPP22	,	2.2	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	308	},
		{	VPP23	,	2.3	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	304	},
		{	VPP24	,	2.4	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	300	},
		{	VPP25	,	2.5	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	296	},
		{	VPP26	,	2.6	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	292	},
		{	VPP27	,	2.7	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	288	},
		{	VPP28	,	2.8	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	284	},
		{	VPP29	,	2.9	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	280	},
		{	VPP30	,	3.0	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	276	},
		{	VPP31	,	3.1	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	272	},
		{	VPP32	,	3.2	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	268	},
		{	VPP33	,	3.3	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	264	},
		{	VPP34	,	3.4	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	260	},
		{	VPP35	,	3.5	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	256	},
		{	VPP36	,	3.6	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	252	},
		{	VPP37	,	3.7	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	248	},
		{	VPP38	,	3.8	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	244	},
		{	VPP39	,	3.9	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	240	},
		{	VPP40	,	4.0	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	236	},
		{	VPP41	,	4.1	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	232	},
		{	VPP42	,	4.2	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	228	},
		{	VPP43	,	4.3	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	224	},
		{	VPP44	,	4.4	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	220	},
		{	VPP45	,	4.5	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	216	},
		{	VPP46	,	4.6	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	212	},
		{	VPP47	,	4.7	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	208	},
		{	VPP48	,	4.8	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	204	},
		{	VPP49	,	4.9	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	200	},
		{	VPP50	,	5.0	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	196	},
		{	VPP51	,	5.1	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	192	},
		{	VPP52	,	5.2	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	188	},
		{	VPP53	,	5.3	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	184	},
		{	VPP54	,	5.4	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	180	},
		{	VPP55	,	5.5	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	176	},
		{	VPP56	,	5.6	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	172	},
		{	VPP57	,	5.7	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	168	},
		{	VPP58	,	5.8	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	164	},
		{	VPP59	,	5.9	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	160	},
		{	VPP60	,	6.0	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	156	},
		{	VPP61	,	6.1	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	152	},
		{	VPP62	,	6.2	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	148	},
		{	VPP63	,	6.3	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	144	},
		{	VPP64	,	6.4	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	140	},
		{	VPP65	,	6.5	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	136	},
		{	VPP66	,	6.6	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	132	},
		{	VPP67	,	6.7	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	128	},
		{	VPP68	,	6.8	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	124	},
		{	VPP69	,	6.9	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	120	},
		{	VPP70	,	7.0	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	116	},
		{	VPP71	,	7.1	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	112	},
		{	VPP72	,	7.2	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	108	},
		{	VPP73	,	7.3	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	104	},
		{	VPP74	,	7.4	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	100	},
		{	VPP75	,	7.5	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	96	},
		{	VPP76	,	7.6	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	92	},
		{	VPP77	,	7.7	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	88	},
		{	VPP78	,	7.8	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	84	},
		{	VPP79	,	7.9	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	80	},
		{	VPP80	,	8.0	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	76	},
		{	VPP81	,	8.1	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	72	},
		{	VPP82	,	8.2	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	68	},
		{	VPP83	,	8.3	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	64	},
		{	VPP84	,	8.4	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	60	},
		{	VPP85	,	8.5	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	56	},
		{	VPP86	,	8.6	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	52	},
		{	VPP87	,	8.7	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	48	},
		{	VPP88	,	8.8	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	44	},
		{	VPP89	,	8.9	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	40	},
		{	VPP90	,	9.0	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	36	},
		{	VPP91	,	9.1	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	32	},
		{	VPP92	,	9.2	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	28	},
		{	VPP93	,	9.3	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	24	},
		{	VPP94	,	9.4	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	20	},
		{	VPP95	,	9.5	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	16	},
		{	VPP96	,	9.6	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	12	},
		{	VPP97	,	9.7	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	8	},
		{	VPP98	,	9.8	,	7	,		0.0		,	0.000	,	AMP_OFFSET	,	4	}
};


// temp location to hold a copy of the lookup table data that is modified by dsp
uint32_t tmpDataTable[SINE_DATA_SIZE];

/*
 * 		Function protochannels
 */
void _ProcessSignalDataTable(float _neg_gain_coeff, float amp_offset, uint16_t _encoder_value);
void VPP_ApplyPresetToSignal(eAmpSettings_t pPresetEnum);

void _ProcessSyncDataTable(float _neg_gain_coeff, float amp_offset, uint16_t _encoder_value);
void VPP_ApplyPresetToSync(eAmpSettings_t pPresetEnum);


/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void VPP_ApplyPresetToSignal(eAmpSettings_t pPresetEnum)
{
	// retrieve the next preset
	AmplitudeProfile_t* pNextEncPreset = &theAmpProfiles[pPresetEnum];

	// Set the new  amp profile to the SignalChannel object
	SM_GetOutputChannel(SIGNAL_CHANNEL)->amp_profile = pNextEncPreset;

    // set the gain preset
	GO_ApplyPresetToSignal(pNextEncPreset->gain_preset);

    // Apply the next amplitude setting to the SignalChannel object
    _ProcessSignalDataTable(pNextEncPreset->neg_gain_coeff, pNextEncPreset->amp_offset , pNextEncPreset->epos);


}

/*
 *
 *	@brief
 *
 *	@param None
 *	@retval None
 *
 */
void VPP_ApplyPresetToSync(eAmpSettings_t pPresetEnum)
{
	// retrieve the next preset
	AmplitudeProfile_t* pNextEncPreset = &theAmpProfiles[pPresetEnum];

	// Set the new VPP Preset to the SyncChannel object
	SM_GetOutputChannel(SYNC_CHANNEL)->amp_profile = pNextEncPreset;

	 // set the gain preset
	GO_ApplyPresetToSync(pNextEncPreset->gain_preset);

	// Apply the next amplitude setting to the SyncChannel object
	_ProcessSyncDataTable(pNextEncPreset->neg_gain_coeff, pNextEncPreset->amp_offset , pNextEncPreset->epos);



}

/*
 *
 *	@brief	amplitude/offset DSP function for Signal output
 *
 *	@param None
 *	@retval None
 *
 */
void _ProcessSignalDataTable(float _neg_gain_coeff, float amp_offset, uint16_t _encoder_value)
{
	sOutputChannel_t * pTmpOutputChannel = SM_GetOutputChannel(SIGNAL_CHANNEL);
	if(pTmpOutputChannel->func_profile->func != PWM_FUNC_MODE)
	{
		// copy refer lookup datat table from SignalChannel object
		for(int i = 0; i < SINE_DATA_SIZE; i++)
		{
			tmpDataTable[i] = pTmpOutputChannel->ref_lut_data[i];
		}

		// calculate positive offset coefficient from encoder position
		float pos_offset_coeff = 1;
		if(_encoder_value)
		{
			pos_offset_coeff = (_encoder_value/4);
		}

		// adjust amplitude and offset of lookup table copy
		for(int i = 0; i < SINE_DATA_SIZE; i++)
		{
			tmpDataTable[i] = tmpDataTable[i] * (_neg_gain_coeff);
			tmpDataTable[i] = tmpDataTable[i] + (AMP_OFFSET * pos_offset_coeff);
		}

		// restore lookup table copy to active lookup table in SignalChannel object
		for(int i = 0; i < SINE_DATA_SIZE; i++)
		{
			SM_GetOutputChannel(SIGNAL_CHANNEL)->dsp_lut_data[i] = tmpDataTable[i];
		}
	}

}

/*
 *
 *	@brief	amplitude/offset DSP function for Sync output
 *
 *	@param None
 *	@retval None
 *
 */
void _ProcessSyncDataTable(float _neg_gain_coeff, float amp_offset, uint16_t _encoder_value)
{
	if(SM_GetOutputChannel(SYNC_CHANNEL)->func_profile->func != PWM_FUNC_MODE)
	{
		// copy refer lookup datat table from SyncChannel object
		for(int i = 0; i < SINE_DATA_SIZE; i++)
		{
			tmpDataTable[i] = SM_GetOutputChannel(SYNC_CHANNEL)->ref_lut_data[i];
		}

		// calculate positive offset coefficient from encoder position
		float pos_offset_coeff = 1;
		if(_encoder_value)
		{
			pos_offset_coeff = (_encoder_value/4);
		}

		// adjust amplitude and offset of lookup table copy
		for(int i = 0; i < SINE_DATA_SIZE; i++)
		{

			tmpDataTable[i] = tmpDataTable[i] * (_neg_gain_coeff);
			tmpDataTable[i] = tmpDataTable[i] + (AMP_OFFSET * pos_offset_coeff);
		}
	}


	// restore lookup table copy to active lookup table in SignalChannel object
	for(int i = 0; i < SINE_DATA_SIZE; i++)
	{
		SM_GetOutputChannel(SYNC_CHANNEL)->dsp_lut_data[i] = tmpDataTable[i];
	}
}



/*
 *
 *	@brief Get VPP preset pointer
 *
 *	@param None
 *	@retval pointer to AmplitudeProfile_t struct
 *
 */
/*
AmplitudeProfile_t * VPP_GetVppPresetObject(eVppActivePresetSelect_t eVppActivePresetSelect)
{
	if(eVppActivePresetSelect)
		return pSyncVppEncoderPreset;
	else
		return pSignalVppEncoderPreset;
}
*/


/*
 *
 *	@brief Search array of structs for preset
 *
 *	@param Search criteria. Should be one of the following:
 *
 *	VPP01, 	VPP02,	VPP03,	VPP04,	VPP05,	VPP06,	VPP07,	VPP08,	VPP09,	VPP10,	VPP11,	VPP12,	VPP13,	VPP14,	VPP15,
	VPP16,	VPP17,	VPP18,	VPP19,	VPP20,	VPP21,	VPP22,	VPP23,	VPP24,	VPP25,	VPP26,	VPP27,	VPP28,	VPP29,	VPP30,
	VPP31,	VPP32,	VPP33,	VPP34,	VPP35,	VPP36,	VPP37,	VPP38,	VPP39,	VPP40,	VPP41,  VPP42,  VPP43,	VPP44,	VPP45,
	VPP46,	VPP47,	VPP48,	VPP49,	VPP50,	VPP51,	VPP52,	VPP53,	VPP54,	VPP55,	VPP56,	VPP57,	VPP58,	VPP59,	VPP60,
	VPP61,	VPP62,	VPP63,	VPP64,	VPP65,	VPP66,	VPP67,	VPP68,	VPP69,	VPP70,	VPP71,	VPP72,	VPP73,  VPP74,	VPP75,
	VPP76,	VPP77,	VPP78,	VPP79,	VPP80,	VPP81,	VPP82,	VPP83,	VPP84,	VPP85,	VPP86,	VPP87,	VPP88,	VPP89,	VPP90,
	VPP91,	VPP92,	VPP93,	VPP94,	VPP95,	VPP96,	VPP97,	VPP98,

 *	@retval pointer to AmplitudeProfile_t struct
 *
 */
AmplitudeProfile_t * VPP_FindVppPresetObject(eAmpSettings_t pEnum)
{
	for(int i = 0; i < MAX_VPP_PRESETS; i++ )
	{
		if(theAmpProfiles[i].amp_setting == pEnum)
		{
			return &theAmpProfiles[i];
		}
	}
	// error!
	DM_SetErrorDebugMsg("VPP_FindVppPresetObject(): AmplitudeProfile_t obj not found");
	return 0;
}




/*
 *
 *	@brief multiplex encoder input -> preset function
 *
 *	@param Should be one of the following:
 *
 *	VPP01, 	VPP02,	VPP03,	VPP04,	VPP05,	VPP06,	VPP07,	VPP08,	VPP09,	VPP10,	VPP11,	VPP12,	VPP13,	VPP14,	VPP15,
	VPP16,	VPP17,	VPP18,	VPP19,	VPP20,	VPP21,	VPP22,	VPP23,	VPP24,	VPP25,	VPP26,	VPP27,	VPP28,	VPP29,	VPP30,
	VPP31,	VPP32,	VPP33,	VPP34,	VPP35,	VPP36,	VPP37,	VPP38,	VPP39,	VPP40,	VPP41,  VPP42,  VPP43,	VPP44,	VPP45,
	VPP46,	VPP47,	VPP48,	VPP49,	VPP50,	VPP51,	VPP52,	VPP53,	VPP54,	VPP55,	VPP56,	VPP57,	VPP58,	VPP59,	VPP60,
	VPP61,	VPP62,	VPP63,	VPP64,	VPP65,	VPP66,	VPP67,	VPP68,	VPP69,	VPP70,	VPP71,	VPP72,	VPP73,  VPP74,	VPP75,
	VPP76,	VPP77,	VPP78,	VPP79,	VPP80,	VPP81,	VPP82,	VPP83,	VPP84,	VPP85,	VPP86,	VPP87,	VPP88,	VPP89,	VPP90,
	VPP91,	VPP92,	VPP93,	VPP94,	VPP95,	VPP96,	VPP97,	VPP98,

 *	@retval None
 *
 */
void VPP_ModifySignalOutput(uint16_t pEncoderValue)
{
	switch(pEncoderValue)
	{
		case 0	:
		case 1	:
		case 2	:
			VPP_ApplyPresetToSignal( VPP01 );
			break;
		case 3	:
		case 4	:
		case 5	:
		case 6	:
			VPP_ApplyPresetToSignal( VPP02	);
			break;
		case 7	:
		case 8	:
		case 9	:
		case 10	:
			VPP_ApplyPresetToSignal( VPP03	);
			break;
		case 11	:
		case 12	:
		case 13	:
		case 14	:
			VPP_ApplyPresetToSignal( VPP04	);
			break;
		case 15	:
		case 16	:
		case 17	:
		case 18	:
			VPP_ApplyPresetToSignal( VPP05	);
			break;
		case 19	:
		case 20	:
		case 21	:
		case 22	:
			VPP_ApplyPresetToSignal( VPP06	);
			break;
		case 23	:
		case 24	:
		case 25	:
		case 26	:
			VPP_ApplyPresetToSignal( VPP07	);
			break;
		case 27	:
		case 28	:
		case 29	:
		case 30	:
			VPP_ApplyPresetToSignal( VPP08	);
			break;
		case 31	:
		case 32	:
		case 33	:
		case 34	:
			VPP_ApplyPresetToSignal( VPP09	);
			break;
		case 35	:
		case 36	:
		case 37	:
		case 38	:
			VPP_ApplyPresetToSignal( VPP10	);
			break;
		case 39	:
		case 40	:
		case 41	:
		case 42	:
			VPP_ApplyPresetToSignal( VPP11	);
			break;
		case 43	:
		case 44	:
		case 45	:
		case 46	:
			VPP_ApplyPresetToSignal( VPP12	);
			break;
		case 47	:
		case 48	:
		case 49	:
		case 50	:
			VPP_ApplyPresetToSignal( VPP13	);
			break;
		case 51	:
		case 52	:
		case 53	:
		case 54	:
			VPP_ApplyPresetToSignal( VPP14	);
			break;
		case 55	:
		case 56	:
		case 57	:
		case 58	:
			VPP_ApplyPresetToSignal( VPP15	);
			break;
		case 59	:
		case 60	:
		case 61	:
		case 62	:
			VPP_ApplyPresetToSignal( VPP16	);
			break;
		case 63	:
		case 64	:
		case 65	:
		case 66	:
			VPP_ApplyPresetToSignal( VPP17	);
			break;
		case 67	:
		case 68	:
		case 69	:
		case 70	:
			VPP_ApplyPresetToSignal( VPP18	);
			break;
		case 71	:
		case 72	:
		case 73	:
		case 74	:
			VPP_ApplyPresetToSignal( VPP19	);
			break;
		case 75	:
		case 76	:
		case 77	:
		case 78	:
			VPP_ApplyPresetToSignal( VPP20	);
			break;
		case 79	:
		case 80	:
		case 81	:
		case 82	:
			VPP_ApplyPresetToSignal( VPP21	);
			break;
		case 83	:
		case 84	:
		case 85	:
		case 86	:
			VPP_ApplyPresetToSignal( VPP22	);
			break;
		case 87	:
		case 88	:
		case 89	:
		case 90	:
			VPP_ApplyPresetToSignal( VPP23	);
			break;
		case 91	:
		case 92	:
		case 93	:
		case 94	:
			VPP_ApplyPresetToSignal( VPP24	);
			break;
		case 95	:
		case 96	:
		case 97	:
		case 98	:
			VPP_ApplyPresetToSignal( VPP25	);
			break;
		case 99		:
		case 100	:
		case 101	:
		case 102	:
			VPP_ApplyPresetToSignal( VPP26	);
			break;
		case 103	:
		case 104	:
		case 105	:
		case 106	:
			VPP_ApplyPresetToSignal( VPP27	);
			break;
		case 107	:
		case 108	:
		case 109	:
		case 110	:
			VPP_ApplyPresetToSignal( VPP28	);
			break;
		case 111	:
		case 112	:
		case 113	:
		case 114	:
			VPP_ApplyPresetToSignal( VPP29	);
			break;
		case 115	:
		case 116	:
		case 117	:
		case 118	:
			VPP_ApplyPresetToSignal( VPP30	);
			break;
		case 119	:
		case 120	:
		case 121	:
		case 122	:
			VPP_ApplyPresetToSignal( VPP31	);
			break;
		case 123	:
		case 124	:
		case 125	:
		case 126	:
			VPP_ApplyPresetToSignal( VPP32	);
			break;
		case 127	:
		case 128	:
		case 129	:
		case 130	:
			VPP_ApplyPresetToSignal( VPP33	);
			break;
		case 131	:
		case 132	:
		case 133	:
		case 134	:
			VPP_ApplyPresetToSignal( VPP34	);
			break;
		case 135	:
		case 136	:
		case 137	:
		case 138	:
			VPP_ApplyPresetToSignal( VPP35	);
			break;
		case 139	:
		case 140	:
		case 141	:
		case 142	:
			VPP_ApplyPresetToSignal( VPP36	);
			break;
		case 143	:
		case 144	:
		case 145	:
		case 146	:
			VPP_ApplyPresetToSignal( VPP37	);
			break;
		case 147	:
		case 148	:
		case 149	:
		case 150	:
			VPP_ApplyPresetToSignal( VPP38	);
			break;
		case 151	:
		case 152	:
		case 153	:
		case 154	:
			VPP_ApplyPresetToSignal( VPP39	);
			break;
		case 155	:
		case 156	:
		case 157	:
		case 158	:
			VPP_ApplyPresetToSignal( VPP40	);
			break;
		case 159	:
		case 160	:
		case 161	:
		case 162	:
			VPP_ApplyPresetToSignal( VPP41	);
			break;
		case 163	:
		case 164	:
		case 165	:
		case 166	:
			VPP_ApplyPresetToSignal( VPP42	);
			break;
		case 167	:
		case 168	:
		case 169	:
		case 170	:
			VPP_ApplyPresetToSignal( VPP43	);
			break;
		case 171	:
		case 172	:
		case 173	:
		case 174	:
			VPP_ApplyPresetToSignal( VPP44	);
			break;
		case 175	:
		case 176	:
		case 177	:
		case 178	:
			VPP_ApplyPresetToSignal( VPP45	);
			break;
		case 179	:
		case 180	:
		case 181	:
		case 182	:
			VPP_ApplyPresetToSignal( VPP46	);
			break;
		case 183	:
		case 184	:
		case 185	:
		case 186	:
			VPP_ApplyPresetToSignal( VPP47	);
			break;
		case 187	:
		case 188	:
		case 189	:
		case 190	:
			VPP_ApplyPresetToSignal( VPP48	);
			break;
		case 191	:
		case 192	:
		case 193	:
		case 194	:
			VPP_ApplyPresetToSignal( VPP49	);
			break;
		case 195	:
		case 196	:
		case 197	:
		case 198	:
			VPP_ApplyPresetToSignal( VPP50	);
			break;
		case 199	:
		case 200	:
		case 201	:
		case 202	:
			VPP_ApplyPresetToSignal( VPP51	);
			break;
		case 203	:
		case 204	:
		case 205	:
		case 206	:
			VPP_ApplyPresetToSignal( VPP52	);
			break;
		case 207	:
		case 208	:
		case 209	:
		case 210	:
			VPP_ApplyPresetToSignal( VPP53	);
			break;
		case 211	:
		case 212	:
		case 213	:
		case 214	:
			VPP_ApplyPresetToSignal( VPP54	);
			break;
		case 215	:
		case 216	:
		case 217	:
		case 218	:
			VPP_ApplyPresetToSignal( VPP55	);
			break;
		case 219	:
		case 220	:
		case 221	:
		case 222	:
			VPP_ApplyPresetToSignal( VPP56	);
			break;
		case 223	:
		case 224	:
		case 225	:
		case 226	:
			VPP_ApplyPresetToSignal( VPP57	);
			break;
		case 227	:
		case 228	:
		case 229	:
		case 230	:
			VPP_ApplyPresetToSignal( VPP58	);
			break;
		case 231	:
		case 232	:
		case 233	:
		case 234	:
			VPP_ApplyPresetToSignal( VPP59	);
			break;
		case 235	:
		case 236	:
		case 237	:
		case 238	:
			VPP_ApplyPresetToSignal( VPP60	);
			break;
		case 239	:
		case 240	:
		case 241	:
		case 242	:
			VPP_ApplyPresetToSignal( VPP61	);
			break;
		case 243	:
		case 244	:
		case 245	:
		case 246	:
			VPP_ApplyPresetToSignal( VPP62	);
			break;
		case 247	:
		case 248	:
		case 249	:
		case 250	:
			VPP_ApplyPresetToSignal( VPP63	);
			break;
		case 251	:
		case 252	:
		case 253	:
		case 254	:
			VPP_ApplyPresetToSignal( VPP64	);
			break;
		case 255	:
		case 256	:
		case 257	:
		case 258	:
			VPP_ApplyPresetToSignal( VPP65	);
			break;
		case 259	:
		case 260	:
		case 261	:
		case 262	:
			VPP_ApplyPresetToSignal( VPP66	);
			break;
		case 263	:
		case 264	:
		case 265	:
		case 266	:
			VPP_ApplyPresetToSignal( VPP67	);
			break;
		case 267	:
		case 268	:
		case 269	:
		case 270	:
			VPP_ApplyPresetToSignal( VPP68	);
			break;
		case 271	:
		case 272	:
		case 273	:
		case 274	:
			VPP_ApplyPresetToSignal( VPP69	);
			break;
		case 275	:
		case 276	:
		case 277	:
		case 278	:
			VPP_ApplyPresetToSignal( VPP70	);
			break;
		case 279	:
		case 280	:
		case 281	:
		case 282	:
			VPP_ApplyPresetToSignal( VPP71	);
			break;
		case 283	:
		case 284	:
		case 285	:
		case 286	:
			VPP_ApplyPresetToSignal( VPP72	);
			break;
		case 287	:
		case 288	:
		case 289	:
		case 290	:
			VPP_ApplyPresetToSignal( VPP73	);
			break;
		case 291	:
		case 292	:
		case 293	:
		case 294	:
			VPP_ApplyPresetToSignal( VPP74	);
			break;
		case 295	:
		case 296	:
		case 297	:
		case 298	:
			VPP_ApplyPresetToSignal( VPP75	);
			break;
		case 299	:
		case 300	:
		case 301	:
		case 302	:
			VPP_ApplyPresetToSignal( VPP76	);
			break;
		case 303	:
		case 304	:
		case 305	:
		case 306	:
			VPP_ApplyPresetToSignal( VPP77	);
			break;
		case 307	:
		case 308	:
		case 309	:
		case 310	:
			VPP_ApplyPresetToSignal( VPP78	);
			break;
		case 311	:
		case 312	:
		case 313	:
		case 314	:
			VPP_ApplyPresetToSignal( VPP79	);
			break;
		case 315	:
		case 316	:
		case 317	:
		case 318	:
			VPP_ApplyPresetToSignal( VPP80	);
			break;
		case 319	:
		case 320	:
		case 321	:
		case 322	:
			VPP_ApplyPresetToSignal( VPP81	);
			break;
		case 323	:
		case 324	:
		case 325	:
		case 326	:
			VPP_ApplyPresetToSignal( VPP82	);
			break;
		case 327	:
		case 328	:
		case 329	:
		case 330	:
			VPP_ApplyPresetToSignal( VPP83	);
			break;
		case 331	:
		case 332	:
		case 333	:
		case 334	:
			VPP_ApplyPresetToSignal( VPP84	);
			break;
		case 335	:
		case 336	:
		case 337	:
		case 338	:
			VPP_ApplyPresetToSignal( VPP85	);
			break;
		case 339	:
		case 340	:
		case 341	:
		case 342	:
			VPP_ApplyPresetToSignal( VPP86	);
			break;
		case 343	:
		case 344	:
		case 345	:
		case 346	:
			VPP_ApplyPresetToSignal( VPP87	);
			break;
		case 347	:
		case 348	:
		case 349	:
		case 350	:
			VPP_ApplyPresetToSignal( VPP88	);
			break;
		case 351	:
		case 352	:
		case 353	:
		case 354	:
			VPP_ApplyPresetToSignal( VPP89	);
			break;
		case 355	:
		case 356	:
		case 357	:
		case 358	:
			VPP_ApplyPresetToSignal( VPP90	);
			break;
		case 359	:
		case 360	:
		case 361	:
		case 362	:
			VPP_ApplyPresetToSignal( VPP91	);
			break;
		case 363	:
		case 364	:
		case 365	:
		case 366	:
			VPP_ApplyPresetToSignal( VPP92	);
			break;
		case 367	:
		case 368	:
		case 369	:
		case 370	:
			VPP_ApplyPresetToSignal( VPP93	);
			break;
		case 371	:
		case 372	:
		case 373	:
		case 374	:
			VPP_ApplyPresetToSignal( VPP94	);
			break;
		case 375	:
		case 376	:
		case 377	:
		case 378	:
			VPP_ApplyPresetToSignal( VPP95	);
			break;
		case 379	:
		case 380	:
		case 381	:
		case 382	:
			VPP_ApplyPresetToSignal( VPP96	);
			break;
		case 383	:
		case 384	:
		case 385	:
		case 386	:
			VPP_ApplyPresetToSignal( VPP97	);
			break;
		case 387	:
		case 388	:
		case 389	:
		case 390	:
			VPP_ApplyPresetToSignal( VPP98	);
			break;

		default:
			break;
	}
}

/*
 *
 *	@brief multiplex encoder input -> preset function
 *
 *	@param Should be one of the following:
 *
 *	VPP01, 	VPP02,	VPP03,	VPP04,	VPP05,	VPP06,	VPP07,	VPP08,	VPP09,	VPP10,	VPP11,	VPP12,	VPP13,	VPP14,	VPP15,
	VPP16,	VPP17,	VPP18,	VPP19,	VPP20,	VPP21,	VPP22,	VPP23,	VPP24,	VPP25,	VPP26,	VPP27,	VPP28,	VPP29,	VPP30,
	VPP31,	VPP32,	VPP33,	VPP34,	VPP35,	VPP36,	VPP37,	VPP38,	VPP39,	VPP40,	VPP41,  VPP42,  VPP43,	VPP44,	VPP45,
	VPP46,	VPP47,	VPP48,	VPP49,	VPP50,	VPP51,	VPP52,	VPP53,	VPP54,	VPP55,	VPP56,	VPP57,	VPP58,	VPP59,	VPP60,
	VPP61,	VPP62,	VPP63,	VPP64,	VPP65,	VPP66,	VPP67,	VPP68,	VPP69,	VPP70,	VPP71,	VPP72,	VPP73,  VPP74,	VPP75,
	VPP76,	VPP77,	VPP78,	VPP79,	VPP80,	VPP81,	VPP82,	VPP83,	VPP84,	VPP85,	VPP86,	VPP87,	VPP88,	VPP89,	VPP90,
	VPP91,	VPP92,	VPP93,	VPP94,	VPP95,	VPP96,	VPP97,	VPP98,

 *	@retval None
 *
 */
void VPP_ModifySyncOutput(uint16_t pEncoderValue)
{
	switch(pEncoderValue)
	{
		case 0	:
		case 1	:
		case 2	:
			VPP_ApplyPresetToSync( VPP01 );
			break;
		case 3	:
		case 4	:
		case 5	:
		case 6	:
			VPP_ApplyPresetToSync( VPP02	);
			break;
		case 7	:
		case 8	:
		case 9	:
		case 10	:
			VPP_ApplyPresetToSync( VPP03	);
			break;
		case 11	:
		case 12	:
		case 13	:
		case 14	:
			VPP_ApplyPresetToSync( VPP04	);
			break;
		case 15	:
		case 16	:
		case 17	:
		case 18	:
			VPP_ApplyPresetToSync( VPP05	);
			break;
		case 19	:
		case 20	:
		case 21	:
		case 22	:
			VPP_ApplyPresetToSync( VPP06	);
			break;
		case 23	:
		case 24	:
		case 25	:
		case 26	:
			VPP_ApplyPresetToSync( VPP07	);
			break;
		case 27	:
		case 28	:
		case 29	:
		case 30	:
			VPP_ApplyPresetToSync( VPP08	);
			break;
		case 31	:
		case 32	:
		case 33	:
		case 34	:
			VPP_ApplyPresetToSync( VPP09	);
			break;
		case 35	:
		case 36	:
		case 37	:
		case 38	:
			VPP_ApplyPresetToSync( VPP10	);
			break;
		case 39	:
		case 40	:
		case 41	:
		case 42	:
			VPP_ApplyPresetToSync( VPP11	);
			break;
		case 43	:
		case 44	:
		case 45	:
		case 46	:
			VPP_ApplyPresetToSync( VPP12	);
			break;
		case 47	:
		case 48	:
		case 49	:
		case 50	:
			VPP_ApplyPresetToSync( VPP13	);
			break;
		case 51	:
		case 52	:
		case 53	:
		case 54	:
			VPP_ApplyPresetToSync( VPP14	);
			break;
		case 55	:
		case 56	:
		case 57	:
		case 58	:
			VPP_ApplyPresetToSync( VPP15	);
			break;
		case 59	:
		case 60	:
		case 61	:
		case 62	:
			VPP_ApplyPresetToSync( VPP16	);
			break;
		case 63	:
		case 64	:
		case 65	:
		case 66	:
			VPP_ApplyPresetToSync( VPP17	);
			break;
		case 67	:
		case 68	:
		case 69	:
		case 70	:
			VPP_ApplyPresetToSync( VPP18	);
			break;
		case 71	:
		case 72	:
		case 73	:
		case 74	:
			VPP_ApplyPresetToSync( VPP19	);
			break;
		case 75	:
		case 76	:
		case 77	:
		case 78	:
			VPP_ApplyPresetToSync( VPP20	);
			break;
		case 79	:
		case 80	:
		case 81	:
		case 82	:
			VPP_ApplyPresetToSync( VPP21	);
			break;
		case 83	:
		case 84	:
		case 85	:
		case 86	:
			VPP_ApplyPresetToSync( VPP22	);
			break;
		case 87	:
		case 88	:
		case 89	:
		case 90	:
			VPP_ApplyPresetToSync( VPP23	);
			break;
		case 91	:
		case 92	:
		case 93	:
		case 94	:
			VPP_ApplyPresetToSync( VPP24	);
			break;
		case 95	:
		case 96	:
		case 97	:
		case 98	:
			VPP_ApplyPresetToSync( VPP25	);
			break;
		case 99		:
		case 100	:
		case 101	:
		case 102	:
			VPP_ApplyPresetToSync( VPP26	);
			break;
		case 103	:
		case 104	:
		case 105	:
		case 106	:
			VPP_ApplyPresetToSync( VPP27	);
			break;
		case 107	:
		case 108	:
		case 109	:
		case 110	:
			VPP_ApplyPresetToSync( VPP28	);
			break;
		case 111	:
		case 112	:
		case 113	:
		case 114	:
			VPP_ApplyPresetToSync( VPP29	);
			break;
		case 115	:
		case 116	:
		case 117	:
		case 118	:
			VPP_ApplyPresetToSync( VPP30	);
			break;
		case 119	:
		case 120	:
		case 121	:
		case 122	:
			VPP_ApplyPresetToSync( VPP31	);
			break;
		case 123	:
		case 124	:
		case 125	:
		case 126	:
			VPP_ApplyPresetToSync( VPP32	);
			break;
		case 127	:
		case 128	:
		case 129	:
		case 130	:
			VPP_ApplyPresetToSync( VPP33	);
			break;
		case 131	:
		case 132	:
		case 133	:
		case 134	:
			VPP_ApplyPresetToSync( VPP34	);
			break;
		case 135	:
		case 136	:
		case 137	:
		case 138	:
			VPP_ApplyPresetToSync( VPP35	);
			break;
		case 139	:
		case 140	:
		case 141	:
		case 142	:
			VPP_ApplyPresetToSync( VPP36	);
			break;
		case 143	:
		case 144	:
		case 145	:
		case 146	:
			VPP_ApplyPresetToSync( VPP37	);
			break;
		case 147	:
		case 148	:
		case 149	:
		case 150	:
			VPP_ApplyPresetToSync( VPP38	);
			break;
		case 151	:
		case 152	:
		case 153	:
		case 154	:
			VPP_ApplyPresetToSync( VPP39	);
			break;
		case 155	:
		case 156	:
		case 157	:
		case 158	:
			VPP_ApplyPresetToSync( VPP40	);
			break;
		case 159	:
		case 160	:
		case 161	:
		case 162	:
			VPP_ApplyPresetToSync( VPP41	);
			break;
		case 163	:
		case 164	:
		case 165	:
		case 166	:
			VPP_ApplyPresetToSync( VPP42	);
			break;
		case 167	:
		case 168	:
		case 169	:
		case 170	:
			VPP_ApplyPresetToSync( VPP43	);
			break;
		case 171	:
		case 172	:
		case 173	:
		case 174	:
			VPP_ApplyPresetToSync( VPP44	);
			break;
		case 175	:
		case 176	:
		case 177	:
		case 178	:
			VPP_ApplyPresetToSync( VPP45	);
			break;
		case 179	:
		case 180	:
		case 181	:
		case 182	:
			VPP_ApplyPresetToSync( VPP46	);
			break;
		case 183	:
		case 184	:
		case 185	:
		case 186	:
			VPP_ApplyPresetToSync( VPP47	);
			break;
		case 187	:
		case 188	:
		case 189	:
		case 190	:
			VPP_ApplyPresetToSync( VPP48	);
			break;
		case 191	:
		case 192	:
		case 193	:
		case 194	:
			VPP_ApplyPresetToSync( VPP49	);
			break;
		case 195	:
		case 196	:
		case 197	:
		case 198	:
			VPP_ApplyPresetToSync( VPP50	);
			break;
		case 199	:
		case 200	:
		case 201	:
		case 202	:
			VPP_ApplyPresetToSync( VPP51	);
			break;
		case 203	:
		case 204	:
		case 205	:
		case 206	:
			VPP_ApplyPresetToSync( VPP52	);
			break;
		case 207	:
		case 208	:
		case 209	:
		case 210	:
			VPP_ApplyPresetToSync( VPP53	);
			break;
		case 211	:
		case 212	:
		case 213	:
		case 214	:
			VPP_ApplyPresetToSync( VPP54	);
			break;
		case 215	:
		case 216	:
		case 217	:
		case 218	:
			VPP_ApplyPresetToSync( VPP55	);
			break;
		case 219	:
		case 220	:
		case 221	:
		case 222	:
			VPP_ApplyPresetToSync( VPP56	);
			break;
		case 223	:
		case 224	:
		case 225	:
		case 226	:
			VPP_ApplyPresetToSync( VPP57	);
			break;
		case 227	:
		case 228	:
		case 229	:
		case 230	:
			VPP_ApplyPresetToSync( VPP58	);
			break;
		case 231	:
		case 232	:
		case 233	:
		case 234	:
			VPP_ApplyPresetToSync( VPP59	);
			break;
		case 235	:
		case 236	:
		case 237	:
		case 238	:
			VPP_ApplyPresetToSync( VPP60	);
			break;
		case 239	:
		case 240	:
		case 241	:
		case 242	:
			VPP_ApplyPresetToSync( VPP61	);
			break;
		case 243	:
		case 244	:
		case 245	:
		case 246	:
			VPP_ApplyPresetToSync( VPP62	);
			break;
		case 247	:
		case 248	:
		case 249	:
		case 250	:
			VPP_ApplyPresetToSync( VPP63	);
			break;
		case 251	:
		case 252	:
		case 253	:
		case 254	:
			VPP_ApplyPresetToSync( VPP64	);
			break;
		case 255	:
		case 256	:
		case 257	:
		case 258	:
			VPP_ApplyPresetToSync( VPP65	);
			break;
		case 259	:
		case 260	:
		case 261	:
		case 262	:
			VPP_ApplyPresetToSync( VPP66	);
			break;
		case 263	:
		case 264	:
		case 265	:
		case 266	:
			VPP_ApplyPresetToSync( VPP67	);
			break;
		case 267	:
		case 268	:
		case 269	:
		case 270	:
			VPP_ApplyPresetToSync( VPP68	);
			break;
		case 271	:
		case 272	:
		case 273	:
		case 274	:
			VPP_ApplyPresetToSync( VPP69	);
			break;
		case 275	:
		case 276	:
		case 277	:
		case 278	:
			VPP_ApplyPresetToSync( VPP70	);
			break;
		case 279	:
		case 280	:
		case 281	:
		case 282	:
			VPP_ApplyPresetToSync( VPP71	);
			break;
		case 283	:
		case 284	:
		case 285	:
		case 286	:
			VPP_ApplyPresetToSync( VPP72	);
			break;
		case 287	:
		case 288	:
		case 289	:
		case 290	:
			VPP_ApplyPresetToSync( VPP73	);
			break;
		case 291	:
		case 292	:
		case 293	:
		case 294	:
			VPP_ApplyPresetToSync( VPP74	);
			break;
		case 295	:
		case 296	:
		case 297	:
		case 298	:
			VPP_ApplyPresetToSync( VPP75	);
			break;
		case 299	:
		case 300	:
		case 301	:
		case 302	:
			VPP_ApplyPresetToSync( VPP76	);
			break;
		case 303	:
		case 304	:
		case 305	:
		case 306	:
			VPP_ApplyPresetToSync( VPP77	);
			break;
		case 307	:
		case 308	:
		case 309	:
		case 310	:
			VPP_ApplyPresetToSync( VPP78	);
			break;
		case 311	:
		case 312	:
		case 313	:
		case 314	:
			VPP_ApplyPresetToSync( VPP79	);
			break;
		case 315	:
		case 316	:
		case 317	:
		case 318	:
			VPP_ApplyPresetToSync( VPP80	);
			break;
		case 319	:
		case 320	:
		case 321	:
		case 322	:
			VPP_ApplyPresetToSync( VPP81	);
			break;
		case 323	:
		case 324	:
		case 325	:
		case 326	:
			VPP_ApplyPresetToSync( VPP82	);
			break;
		case 327	:
		case 328	:
		case 329	:
		case 330	:
			VPP_ApplyPresetToSync( VPP83	);
			break;
		case 331	:
		case 332	:
		case 333	:
		case 334	:
			VPP_ApplyPresetToSync( VPP84	);
			break;
		case 335	:
		case 336	:
		case 337	:
		case 338	:
			VPP_ApplyPresetToSync( VPP85	);
			break;
		case 339	:
		case 340	:
		case 341	:
		case 342	:
			VPP_ApplyPresetToSync( VPP86	);
			break;
		case 343	:
		case 344	:
		case 345	:
		case 346	:
			VPP_ApplyPresetToSync( VPP87	);
			break;
		case 347	:
		case 348	:
		case 349	:
		case 350	:
			VPP_ApplyPresetToSync( VPP88	);
			break;
		case 351	:
		case 352	:
		case 353	:
		case 354	:
			VPP_ApplyPresetToSync( VPP89	);
			break;
		case 355	:
		case 356	:
		case 357	:
		case 358	:
			VPP_ApplyPresetToSync( VPP90	);
			break;
		case 359	:
		case 360	:
		case 361	:
		case 362	:
			VPP_ApplyPresetToSync( VPP91	);
			break;
		case 363	:
		case 364	:
		case 365	:
		case 366	:
			VPP_ApplyPresetToSync( VPP92	);
			break;
		case 367	:
		case 368	:
		case 369	:
		case 370	:
			VPP_ApplyPresetToSync( VPP93	);
			break;
		case 371	:
		case 372	:
		case 373	:
		case 374	:
			VPP_ApplyPresetToSync( VPP94	);
			break;
		case 375	:
		case 376	:
		case 377	:
		case 378	:
			VPP_ApplyPresetToSync( VPP95	);
			break;
		case 379	:
		case 380	:
		case 381	:
		case 382	:
			VPP_ApplyPresetToSync( VPP96	);
			break;
		case 383	:
		case 384	:
		case 385	:
		case 386	:
			VPP_ApplyPresetToSync( VPP97	);
			break;
		case 387	:
		case 388	:
		case 389	:
		case 390	:
			VPP_ApplyPresetToSync( VPP98	);
			break;

		default:
			break;
	}
}




