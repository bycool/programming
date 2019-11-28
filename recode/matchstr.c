 
/**
  * @brief  字符串查找 
  *   @note 支持 通配符 ？ * ,通配符不k可替换空白符  \r \n \t ' '
  * @param  *src:目标串
  * @param  *match:匹配串
	*   @note  *match  连续的*需提前预处理为一个*
  * @param  *re_match_len:匹配串长度	
	* @retval >0 偏移地址 
  * @retval -1 错误 
	* @retval -2 不存在 
  */
int t_str_match(char *src,char *match,uint32_t *re_match_len)
{
	uint32_t i=0,j=0,n=0;
	uint32_t src_len=strlen(src);
	uint32_t  match_len=strlen(match);
	int8_t    tp=0;
	
	if(match_len==0) return -1;
	if(src_len<match_len)return -1;
 
	for(i=0;i<src_len;i++)
	{		
			tp=0;
			n=i;
		  j=0;
			do
			{							
				if(match[j]=='*')
				{
					if(j+1==match_len)//结尾*
					{
						if(src[n]==' ' || src[n]=='\t'|| src[n]=='\r'|| src[n]=='\n' )
						{
							*re_match_len = n-i;
							break;
						}
						else
						{
							n++;
						}
					}
					else//中间*
					{
						if(src[n]==' ' || src[n]=='\t'|| src[n]=='\r'|| src[n]=='\n' )
						{
							tp=-1;
							break;
						}						
						else 
						if(src[n]==match[j+1])
						{
							j++;
						}
						else
						{
							n++;
						}	
					}											
				}	
				else if(src[n]==match[j] || src[n]=='?')
				{					
					j++;
					n++;
				}
				else
				{
					n++;
					tp=-1;
				}	
			}while(j<match_len && n<src_len);
			if(tp==0)
			{
				break;
			}
	}
	
	*re_match_len = n-i;
	if(tp==0&& j==match_len-1) return i;
	return -2;
}
 
 
/**
  * @brief  字符串查找         
  * @param  *src:目标串
  * @param  *match:匹配串
  * @param  *data:结果在目标串中的偏移地址
  * @param  num:最多找到多少个
	* @retval 匹配结果个数 
  */
int t_str_match_all(char *src,char *match,int32_t *data,uint8_t num)
{
	uint32_t i=0,tp=0,n=0,offset=0;
	int re=0;
	uint32_t  match_len=strlen(match);
	uint32_t  src_len=strlen(src);
	uint32_t  re_match_len=0;
	
	char *t_match = (char*)T_MALLOC(match_len+1);
		
	if(t_match==0)return -2;
	
	//连续的*变成一个*
	for(i=0;i<match_len;i++)
	{
		if(match[i]=='*')
		{
			if(tp==0)
			{
				tp=1;
				t_match[n++]=match[i];
			}
			else
			{
			
			}
		}
		else
		{
			tp=0;
			t_match[n++] = match[i];
		}
	}
	t_match[n]=0;
	
	
	
	n=0;
	i=0;
	offset=0;
	do
	{
		re = t_str_match(src+offset,t_match,&re_match_len);
		if(re>0)
		{
			data[i++] = offset+re;
			offset += re + re_match_len;
			n++;
		}	
		
	}while(re>0 && n<num);
	T_FREE(t_match);
	return n;
}

