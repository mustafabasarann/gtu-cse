#include <stdio.h>
#include <math.h>

#define N 8
#define X 10
#define EPSILON 0.0001

// Function to calculate distance between a point and a cluster's center
double calculateDistance(double x, double y, double cluster_x, double cluster_y){
	double distance;
	distance = sqrt((x-cluster_x) * (x-cluster_x) + (y-cluster_y) * (y-cluster_y));
	return distance;
}

// Funciton to calculate percentage difference between two distances
double calculatePercentageDifference(double closest1, double closest2){
	return (fabs(closest1 - closest2) / ((closest1+closest2 + EPSILON) / 2)); // EPSILON for avoid divison by zero
}

int main() {

double cluster1_x,cluster1_y,cluster2_x,cluster2_y,cluster3_x,cluster3_y;
double x,y;
double distance1 , distance2, distance3, closest1, closest2;
int z,num_of1 = 1, num_of2 = 1, num_of3 = 1;

	// Reading initial cluster centers  from user
	scanf("%lf %lf",&cluster1_x,&cluster1_y);
	printf("Point included in Cluster 1\n");
	scanf("%lf %lf",&cluster2_x,&cluster2_y);
	printf("Point included in Cluster 2\n");
	scanf("%lf %lf",&cluster3_x,&cluster3_y);
	printf("Point included in Cluster 3\n");
	
//store cluster centers
double old_x1 = cluster1_x, old_y1 = cluster1_y, old_x2 = cluster2_x, old_y2 = cluster2_y, old_x3 = cluster3_x, old_y3 =cluster3_y;
double new_x1 = old_x1, new_y1 = old_y1;
double new_x2 = old_x2, new_y2 = old_y2;
double new_x3 = old_x3, new_y3 = old_y3;

	// Main loop of program 
	for(int i = 0; i < N-3; i++){
		// reading a point's coordinates
		//printf("Enter a point's coordinate: ");
		scanf("%lf %lf",&x,&y);
		
		//calculating distances between point's and cluster centers
		distance1 = calculateDistance(x,y, cluster1_x, cluster1_y);
		distance2 = calculateDistance(x,y, cluster2_x, cluster2_y);
		distance3 = calculateDistance(x,y, cluster3_x, cluster3_y);
		//finding two closest clusters
		if(distance1 < distance2){
			closest1 = distance1;
			closest2 = distance2;
			z = 1;
		}else{
			closest1 = distance2;
			closest2 = distance1;
			z = 2;
		}
		if(distance3 < closest1){
			closest1 = distance3;
			z = 3;
		}else if(distance3 < closest2){
			closest2 = distance3;
		}
		
	// calculating percentage difference to determine incldue or discard	
		if( X/100 < calculatePercentageDifference(closest1,closest2))
		{
			printf("Point %lf, %lf was included in Cluster %d\n",x,y,z);
			
		}else{
			printf("Point %lf, %lf was discarded.\n",x,y);
			continue;
		}
		
		// updating new cluster centers 
		if(z == 1){
			
			new_x1 = (old_x1 * num_of1 + x) / (num_of1 +1 );
			new_y1 = (old_y1 * num_of1 + y) / (num_of1 +1 );
			num_of1++;
			old_x1 = new_x1;
			old_y1 = new_y1;
			
		}else if(z == 2){
			new_x2 = (old_x2 * num_of2 + x) / (num_of2 +1);
			new_y2 = (old_y2 * num_of2 + y) / (num_of2 +1);
			num_of2++;
			old_x2 = new_x2;
			old_y2 = new_y2;
		}else if(z == 3){
			new_x3 = (old_x3 * num_of3 + x) / (num_of3 +1);
			new_y3 = (old_y3 * num_of3 + y) / (num_of3 +1);
			num_of3++;
			old_x3 = new_x3;
			old_y3 = new_y3;
		}
	}
	//print final cluster centers and number of points included for each cluster
	printf("Cluster 1: %lf, %lf, %d\n",new_x1,new_y1,num_of1);
	printf("Cluster 2: %lf, %lf, %d\n",new_x2,new_y2,num_of2);
	printf("Cluster 3: %lf, %lf, %d\n",new_x3,new_y3,num_of3);
}




