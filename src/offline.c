#include <relic/relic.h>
#include <relic/relic_test.h>
#include <relic/relic_bench.h>
#include<assert.h>
int sign_len=65;
void print_g1(g1_t s){
    uint8_t sign_buf[1024];
    g1_write_bin(sign_buf,1024,s,0);
    for(int i=0;i<sign_len;i++){
        printf("%02x",sign_buf[i]);
    }
    printf("\n");
}
int flag_count[224]={0};
int count=0;
int count2=0;
int process_one_bit(g1_t s,g2_t q,gt_t z){
    uint8_t m[5] = { 0, 1, 2, 3, 4 };
    for(int i=0;i<224;i++){
        g2_t g_2;g2_null(g_2);g2_new(g_2);
        bn_t c1;bn_null(c1);bn_new(c1);
        gt_t z3;gt_null(z3);gt_new(z3);
        gt_t z1;gt_null(z1);gt_new(z1);
        //gt_t z;gt_null(z);gt_new(z);
        
        //gt_get_gen(z);
        bn_set_2b(c1,i);
        g2_mul_gen(g_2,c1);
        pc_map(z1,s,g_2);
        gt_inv(z1,z1);
        gt_mul(z3,z,z1); 
        //g2_mul_gen(q, d);
        if(cp_bbs_ver(s, m, sizeof(m), 0, q, z3) == 1){
                //bn_set_bit(d,i,0);
                printf("find bit %d: %d\n",i,0);
                if(flag_count[i]==0){
                    flag_count[i]=1;
                    count++;
                    printf("count: %d\n",count);
                }
                return 1;
            }
            else{
                gt_inv(z1,z1);
                gt_mul(z3,z,z1);
                if(cp_bbs_ver(s, m, sizeof(m), 0, q, z3) == 1){
                    //bn_set_bit(d,i,1);
                    printf("find bit %d: %d\n",i,1);
                    if(flag_count[i]==0){
                        flag_count[i]=1;
                        count++;
                        printf("count: %d\n",count);
                    }
                    return 1;
                }
                else{
                    //util_printf("cannot verify!\n");
                    //assert(0);
                }                
            }      
    }
    return 0;
}
int main(){
    FILE *fp1=fopen("./sign-1214.txt","r");
    FILE *fp2=fopen("./pp.txt","rb");
    //FILE *fp2=fopen("./pp1.txt","w");
    //FILE *fp3=fopen("./sign.txt","w");
    char sk[1024]={0};
    char pp_q[1024]={0};
    char pp_z[1024]={0};
    char sign_buf[1024]={0};
    char line[1024]={0};
    if (core_init() != RLC_OK) {
		core_clean();
		return 1;
	}
    if (pc_param_set_any() == RLC_OK){
        int code = RLC_ERR;
	    bn_t d;
        bn_t d2;
	    g1_t s;
        g1_t s2;
	    g2_t q;
	    gt_t z;
        gt_t z1;
        uint8_t m[5] = { 0, 1, 2, 3, 4 }, h[RLC_MD_LEN];
        bn_null(d);
        bn_null(d2);
	    g1_null(s);
        g2_null(s2)
	    g2_null(q);
	    gt_null(z);
        gt_null(z1);
        bn_new(d);
        bn_new(d2);
		g1_new(s);
		g2_new(q);
        g2_new(s2);
		gt_new(z);
        gt_new(z1);
        /*if(cp_bbs_gen(d, q, z) == !RLC_OK){
            util_printf("bbs_gen wrong!\n");
        }*/
        
        char pp_q[1024]={0};
        char pp_z[1024]={0};
        size_t q_len;
        size_t z_len;
        fread(&q_len,sizeof(q_len),1,fp2);
        fread(&z_len,sizeof(z_len),1,fp2);
        fread(pp_q,1,q_len,fp2);
        fread(pp_z,1,z_len,fp2);
        g2_read_bin(q,pp_q,q_len);
        gt_read_bin(z,pp_z,z_len);

        char sign_real_bin[1024]={0};
        char sign_real[]="0498dfd2421869a8bc91ed9ad7cf06d459a9fdfe08e836a722c195588d1eb596608eed463a92c8223d11aa18a2384b36c4a3c6899b4978197170334a2dbbfc41e4";
        for(int i=0;i<sign_len;i++){
                int j=2*i;
                char tp[3]={0};
                tp[0]=sign_real[j];
                tp[1]=sign_real[j+1];
                char *endptr;
                sign_real_bin[i]=strtol(tp,&endptr,16);
                //printf("%x ",sign_bin[i]);
            }
        g1_read_bin(s,sign_real_bin,sign_len);

        bn_t t1;bn_null(t1);bn_new(t1);
        
        int num=0;
        uint8_t sign_bin[1024];
        int total=0;
        while(fgets(line,sizeof(line),fp1)!=NULL){
            num++;
            if(strlen(line+8)<10)continue;
            char *line2=line+8;
           
            for(int i=0;i<sign_len;i++){
                int j=2*i;
                char tp[3]={0};
                tp[0]=line2[j];
                tp[1]=line2[j+1];
                char *endptr;
                sign_bin[i]=strtol(tp,&endptr,16);
                //printf("%x ",sign_bin[i]);
            }
            //printf("\n");
            g1_read_bin(s2,sign_bin,sign_len);
            //print_g1(s2);
            if(g1_cmp(s,s2)==RLC_EQ){
                //printf("equal\n");
                
            }
            else{
                printf("not equal, processing\n");
                print_g1(s2);
                int flag=process_one_bit(s2,q,z);
                total++;
                if(!flag){
                    printf("cannot find, not one bit\n");
                    count2++;
                    printf("count2: %d\n",count2);
                }

                
            }

            //g1_null(s2);
            memset(line,0,sizeof(line));
        }
        //printf("s_len: %d\n",s_len);
        printf("total: %d\n",total);
        free(fp1);
        free(fp2);
    }
}